#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qflags.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new Comms(this,ui->cons);
    settings->setWindowFlag(Qt::CustomizeWindowHint);
    settings->setWindowTitle("Ustawienia komunikacji");
    settings->setWindowFlag(Qt::WindowCloseButtonHint,false);
    settings->setWindowFlag(Qt::WindowSystemMenuHint,false);
    settings->setWindowFlag(Qt::WindowMinMaxButtonsHint,false);
    connect(settings,&Comms::status_changed ,this, &MainWindow::change_status);

    timer = new QElapsedTimer();
    timer->start();

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setSource(QUrl("qrc:/qml/main.qml"));
    ui->gridLayout_tab_map->addWidget(container);
    ui->Plot_Yaw->addGraph();
    ui->Plot_Pitch->addGraph();
    ui->Plot_Roll->addGraph();
    ui->Plot_Height->addGraph();
    ui->Plot_Speed->addGraph();
    ui->Plot_Battery->addGraph();
    ui->Plot_Yaw->xAxis->setTickLabels(false);
    ui->Plot_Pitch->xAxis->setTickLabels(false);
    ui->Plot_Roll->xAxis->setTickLabels(false);
    ui->Plot_Height->xAxis->setTickLabels(false);
    ui->Plot_Speed->xAxis->setTickLabels(false);
    ui->Plot_Battery->xAxis->setTickLabels(false);





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_send_button_clicked()
{
    QString tmp;

    tmp=ui->console_send_text->text();
    ui->console_send_text->clear();
    settings->write_data(tmp.toLocal8Bit());
}

void MainWindow::refresh_data(drone_data *data)
{
    //qDebug()<<"Dostalem zmiane";
    double time = double(timer->elapsed())/1000;
    ui->navball->setRotation(data->yaw,data->pitch,data->roll);
        ui->lcd_value->display(data->height);

        if(min_h>data->height){
            min_h=data->height;
        }
        if(max_h<data->height){
            max_h=data->height;
        }


        ui->Plot_Yaw->graph(0)->addData(time,data->yaw);
        ui->Plot_Pitch->graph(0)->addData(time,data->pitch);
        ui->Plot_Roll->graph(0)->addData(time,data->roll);
        ui->Plot_Height->graph(0)->addData(time,data->height);
        ui->Plot_Speed->graph(0)->addData(time,data->speed);
        ui->Plot_Battery->graph(0)->addData(time,data->battery);

        ui->Plot_Yaw->yAxis->setRange(-180,180);
        ui->Plot_Pitch->yAxis->setRange(-180,180);
        ui->Plot_Roll->yAxis->setRange(-180,180);
        ui->Plot_Height->yAxis->setRange(min_h,max_h);
        ui->Plot_Speed->yAxis->setRange(0,30);
        ui->Plot_Battery->yAxis->setRange(0,100);

        ui->Plot_Yaw->graph(0)->data()->removeBefore(time-30<0 ? 0 : time-30);
        ui->Plot_Pitch->graph(0)->data()->removeBefore(time-30<0 ? 0 : time-30);
        ui->Plot_Roll->graph(0)->data()->removeBefore(time-30<0 ? 0 : time-30);
        ui->Plot_Height->graph(0)->data()->removeBefore(time-120<0 ? 0 : time-120);
        ui->Plot_Speed->graph(0)->data()->removeBefore(time-90<0 ? 0 : time-90);
        ui->Plot_Battery->graph(0)->data()->removeBefore(time-120<0 ? 0 : time-120);

        ui->Plot_Yaw->xAxis->setRange(time-30<0 ? 0 : time-30,time);
        ui->Plot_Pitch->xAxis->setRange(time-30<0 ? 0 : time-30,time);
        ui->Plot_Roll->xAxis->setRange(time-30<0 ? 0 : time-30,time);
        ui->Plot_Height->xAxis->setRange(time-120<0 ? 0 : time-120,time);
        ui->Plot_Speed->xAxis->setRange(time-90<0 ? 0 : time-90,time);
        ui->Plot_Battery->xAxis->setRange(time-120<0 ? 0 : time-120,time);


        ui->Plot_Yaw->replot();
        ui->Plot_Pitch->replot();
        ui->Plot_Roll->replot();
        ui->Plot_Height->replot();
        ui->Plot_Speed->replot();
        ui->Plot_Battery->replot();
}

void MainWindow::change_status(QString string)
{
    ui->label_status->setText(string);
}

void MainWindow::on_settings_clicked()
{
    settings->show();
}
