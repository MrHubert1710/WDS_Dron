#include "comms.h"
#include "console.h"
#include "ui_comms.h"
#include "mainwindow.h"

Comms::Comms(QWidget *parent,Console *console) :
    QDialog(parent),
    ui(new Ui::Comms)
{
    cons=console;
    ui->setupUi(this);
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &Comms::read_data);
    parametry = new parser;
    connect(cons,SIGNAL(line_ready(QByteArray)),parametry,SLOT(parseString(QByteArray)));
    connect(parametry,SIGNAL(dataChanged(drone_data*)),parent,SLOT(refresh_data(drone_data*)));
    connect(serial, &QSerialPort::errorOccurred,this,&Comms::closeSerialPort);

}

Comms::~Comms()
{
    delete ui;
}

void Comms::on_pushButton_clicked()
{
    hide();
}

void Comms::on_connect_button_clicked()
{
    serial->setPortName(selected_port);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::StopBits(ONESTOPBIT));
    serial->setFlowControl(QSerialPort::FlowControl(0));

    if(serial->open(QIODevice::ReadWrite)){
        ui->label_status->setText("Połączono!");
        status_changed("Połączono!");
    }else{
        ui->label_status->setText("Błąd łączenia!");
        status_changed("Błąd łączenia!");
        on_search_button_clicked();
    }
}

void Comms::on_search_button_clicked()
{
    closeSerialPort();
    ui->dev_list->clear();
    port_list.clear();
    port_list = QSerialPortInfo::availablePorts();
    foreach(QSerialPortInfo tmp, port_list){
       ui->dev_list->addItem(tmp.portName());
    }
}


void Comms::on_dev_list_itemClicked(QListWidgetItem *item)
{
    selected_port=item->text();
}


void Comms::read_data()
{
    QByteArray data = serial->readAll();
    cons->putData(data,false);
}

void Comms::write_data(const QByteArray &data)
{
    QByteArray tmp(data);
    tmp.append("\n");
    serial->write(tmp);
    cons->putData(tmp,true);
}

void Comms::closeSerialPort()
{
    if(serial->isOpen())
        serial->close();
    ui->label_status->setText("Rozłaczono");
    status_changed("Rozłaczono");
    ui->dev_list->clear();
    port_list.clear();
}
