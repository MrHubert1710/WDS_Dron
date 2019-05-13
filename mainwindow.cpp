#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QElapsedTimer();
    timer->start();

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setSource(QUrl("qrc:/qml/main.qml"));
    ui->gridLayout_tab_map->addWidget(container);
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::read_data);
    parametry = new parser;
    connect(ui->cons,SIGNAL(line_ready(QByteArray)),parametry,SLOT(parseString(QByteArray)));
    connect(parametry,SIGNAL(dataChanged(drone_data*)),this,SLOT(refresh_data(drone_data*)));





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_search_button_clicked()
{
    closeSerialPort();
    ui->dev_list->clear();
    port_list.clear();
    port_list = QSerialPortInfo::availablePorts();
    foreach(QSerialPortInfo tmp, port_list){
        ui->dev_list->addItem(tmp.portName());
    }
}

void MainWindow::on_dev_list_itemClicked(QListWidgetItem *item)
{
    selected_port=item->text();
}

void MainWindow::on_connect_button_clicked()
{
    serial->setPortName(selected_port);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::StopBits(ONESTOPBIT));
    serial->setFlowControl(QSerialPort::FlowControl(0));



    if(serial->open(QIODevice::ReadWrite)){
        ui->label_status->setText("Połączono!");
    }else{
        ui->label_status->setText("Błąd łączenia!");
        on_search_button_clicked();
    }
}

void MainWindow::read_data()
{
    QByteArray data = serial->readAll();
    ui->cons->putData(data,false);
}

void MainWindow::write_data(const QByteArray &data)
{
    QByteArray tmp(data);
    tmp.append("\n");
    serial->write(tmp);
    ui->cons->putData(tmp,true);
}

void MainWindow::closeSerialPort()
{
    if(serial->isOpen())
        serial->close();
    ui->label_status->setText("Rozłaczono");
}


void MainWindow::on_send_button_clicked()
{
    QString tmp;

    tmp=ui->console_send_text->text();
    ui->console_send_text->clear();

    write_data(tmp.toLocal8Bit());
}

void MainWindow::refresh_data(drone_data *data)
{
    qDebug()<<"Dostalem zmiane";
    ui->navball->setRotation(data->yaw,data->pitch,data->roll);
        if(0.95*ui->progressBar->maximum()<data->height){
            ui->progressBar->setMaximum(data->height+100);
            ui->progressBar->setValue(data->height);
            ui->progressBar->setMinimum(data->height-100);
        }else
        if(1.05*ui->progressBar->minimum()>data->height){
            ui->progressBar->setMinimum(data->height-100);
            ui->progressBar->setValue(data->height);
            ui->progressBar->setMaximum(data->height+100);
        }else{
            ui->progressBar->setValue(data->height);
        }
        ui->lcd_min->display(ui->progressBar->minimum());
        ui->lcd_max->display(ui->progressBar->maximum());
        ui->lcd_value->display(ui->progressBar->value());

        if(min_h>data->height){
            min_h=data->height;
        }
        if(max_h<data->height){
            max_h=data->height;
        }

        time.push_back(double(timer->elapsed())/1000);
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

        ui->Plot_Yaw->xAxis->setRange(0,double(timer->elapsed())/1000);
        ui->Plot_Pitch->xAxis->setRange(0,double(timer->elapsed())/1000);
        ui->Plot_Roll->xAxis->setRange(0,double(timer->elapsed())/1000);
        ui->Plot_Height->xAxis->setRange(0,double(timer->elapsed())/1000);
        ui->Plot_Speed->xAxis->setRange(0,double(timer->elapsed())/1000);
        ui->Plot_Battery->xAxis->setRange(0,double(timer->elapsed())/1000);

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
