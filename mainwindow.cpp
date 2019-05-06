#include "mainwindow.h"
#include "ui_mainwindow.h"

void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;

    *s = 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setSource(QUrl("qrc:/qml/main.qml"));
    ui->gridLayout_tab_map->addWidget(container);

    //setup timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), ui->navball , SLOT(nextFrame()));
    connect(m_timer, SIGNAL(timeout()), ui->cons, SLOT(update()));
   // connect(m_timer, SIGNAL(timeout()), this , SLOT(checkstatus_and_readline()));
    m_timer->start(1000 / 100);
    connect(agent,SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this,SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    agent->start();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    //connect(socket,SIGNAL(readyRead()),this,SLOT(checkstatus_and_readline()));
    connect(socket,SIGNAL(stateChanged(QBluetoothSocket::SocketState)),this,SLOT(checkstatus_and_readline()));
    new_parser = new parser;
    connect(new_parser,SIGNAL(dataChanged(drone_data*)),this,SLOT(refresh_items(drone_data*)));
    connect(this,SIGNAL(dataArrived(QString)),new_parser,SLOT(parseString(QString)));
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_progressBar_valueChanged(int value)
{
    int range=ui->progressBar->maximum()+ui->progressBar->minimum();
    ui->progressBar->height();
    ui->label_ah->height();
    ui->label_mnh->height();
    ui->label_mxh->height();
    ui->verticalSpacer_min_actual->maximumSize().height();
    ui->verticalSpacer_actual_max->maximumSize().height();

    int whole_size = ui->progressBar->height();
    int text_size = ui->label_ah->height()+ui->label_mnh->height()+ui->label_mxh->height();
    int spacer_size = whole_size-text_size-2;
    int ma = ((spacer_size*value)/range);
    int am = ((spacer_size*(range-value))/range);
    ui->verticalSpacer_min_actual->changeSize(20,ma,QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->verticalSpacer_actual_max->changeSize(20,am,QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_ah->hide();
    ui->label_ah->show();
    qDebug() << "ma: "<< ma <<" am: " << am;
}

void MainWindow::on_search_button_clicked()
{
    sel_device="";
    agent->stop();
    agent->start();
}

void MainWindow::on_connect_button_clicked()
{
    socket->abort();
    if((ui->dev_list->count()!=0)&&(sel_device!="")){
        socket->connectToService(QBluetoothAddress(sel_device),QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
        qDebug()<<"connecting socket";
    }
}

void MainWindow::on_send_button_clicked()
{
    QString text=ui->console_send_text->text();
    const char * text_c = (text.toStdString()+"\n").c_str();
    socket->write(text_c);
    ui->cons->newItem(std::string(">>")+text.toStdString());
    ui->cons->update();
    ui->console_send_text->clear();
    ui->cons->scrollToBottom();
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->dev_list->addItem(device.address().toString());
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
}

void MainWindow::on_dev_list_itemClicked(QListWidgetItem *item)
{
    sel_device=item->text();
}

void MainWindow::checkstatus_and_readline()
{

    console_line="";
    char cl[1024];
    qint64 lineLength;
    switch(socket->state()){
        case QBluetoothSocket::SocketState::UnconnectedState:
            ui->label_status->setText("Nie połączony");
            break;
        case QBluetoothSocket::SocketState::ServiceLookupState:
            ui->label_status->setText("Szukanie...");
            break;
        case QBluetoothSocket::SocketState::ConnectingState:
            ui->label_status->setText("Łączenie");
            break;
        case QBluetoothSocket::SocketState::ConnectedState:
            ui->label_status->setText("Połączono!");
            socket->write("");
            lineLength = socket->readLine(cl,sizeof(cl));
            if(lineLength != -1){
                chomp(cl);
                console_line=cl;
                dataArrived(console_line);
            }
            ui->cons->newItem(std::string("<<")+console_line.toStdString());
            break;
        case QBluetoothSocket::SocketState::BoundState:
            ui->label_status->setText("Połączono");
            break;
        case QBluetoothSocket::SocketState::ClosingState:
            ui->label_status->setText("Wyłączanie...");
            break;
        case QBluetoothSocket::SocketState::ListeningState:
            ui->label_status->setText("Nasłuchiwanie...");
            break;
    }
    ui->cons->update();
    ui->cons->scrollToBottom();
    //qDebug()<<"readline";

}

void MainWindow::refresh_items(drone_data *data)
{
    ui->navball->setRotation(data->yaw,data->pitch,data->roll);
    if(0.8*ui->progressBar->maximum()<data->height){
        ui->progressBar->setMaximum(data->height+50);
        ui->progressBar->setValue(data->height);
        ui->progressBar->setMinimum(data->height-50);
    }else
    if(1.2*ui->progressBar->minimum()>data->height){
        ui->progressBar->setMinimum(data->height-50);
        ui->progressBar->setValue(data->height);
        ui->progressBar->setMaximum(data->height+50);
    }else{
        ui->progressBar->setValue(data->height);
    }
    ui->label_mnh->setText(QString(ui->progressBar->minimum()));
    ui->label_mxh->setText(QString(ui->progressBar->maximum()));

    if(min_h>data->height){
        min_h=data->height;
    }
    if(max_h<data->height){
        max_h=data->height;
    }

    time.push_back(double(timer.elapsed())/1000);
    yaw.push_back(data->yaw);
    pitch.push_back(data->pitch);
    roll.push_back(data->roll);
    height.push_back(data->height);
    speed.push_back(data->speed);
    battery.push_back(data->battery);
    ui->Plot_Yaw->addGraph();
    ui->Plot_Pitch->addGraph();
    ui->Plot_Roll->addGraph();
    ui->Plot_Height->addGraph();
    ui->Plot_Speed->addGraph();
    ui->Plot_Battery->addGraph();

    ui->Plot_Yaw->graph(0)->setData(time,yaw);
    ui->Plot_Pitch->graph(0)->setData(time,pitch);
    ui->Plot_Roll->graph(0)->setData(time,roll);
    ui->Plot_Height->graph(0)->setData(time,height);
    ui->Plot_Speed->graph(0)->setData(time,speed);
    ui->Plot_Battery->graph(0)->setData(time,battery);

    ui->Plot_Yaw->yAxis->setRange(-180,180);
    ui->Plot_Pitch->yAxis->setRange(-180,180);
    ui->Plot_Roll->yAxis->setRange(-180,180);
    ui->Plot_Height->yAxis->setRange(min_h,max_h);
    ui->Plot_Speed->yAxis->setRange(0,100);
    ui->Plot_Battery->yAxis->setRange(0,100);

    ui->Plot_Yaw->xAxis->setRange(0,double(timer.elapsed())/1000);
    ui->Plot_Pitch->xAxis->setRange(0,double(timer.elapsed())/1000);
    ui->Plot_Roll->xAxis->setRange(0,double(timer.elapsed())/1000);
    ui->Plot_Height->xAxis->setRange(0,double(timer.elapsed())/1000);
    ui->Plot_Speed->xAxis->setRange(0,double(timer.elapsed())/1000);
    ui->Plot_Battery->xAxis->setRange(0,double(timer.elapsed())/1000);

    ui->Plot_Yaw->xAxis->setTickLabels(false);
    ui->Plot_Pitch->xAxis->setTickLabels(false);
    ui->Plot_Roll->xAxis->setTickLabels(false);
    ui->Plot_Height->xAxis->setTickLabels(false);
    ui->Plot_Speed->xAxis->setTickLabels(false);
    ui->Plot_Battery->xAxis->setTickLabels(false);

    ui->Plot_Yaw->replot();
    ui->Plot_Pitch->replot();
    ui->Plot_Roll->replot();
    ui->Plot_Height->replot();
    ui->Plot_Speed->replot();
    ui->Plot_Battery->replot();

}




























