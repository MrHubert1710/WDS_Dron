#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QString>
#include <QQuickView>
#include <QGuiApplication>
#include <QDebug>
#include <QTimer>
#include <string>
#include <cstdlib>
#include <QElapsedTimer>
#include "parser.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_search_button_clicked();

    void on_dev_list_itemClicked(QListWidgetItem *item);

    void on_connect_button_clicked();

    void read_data();

    void write_data(const QByteArray &data);

    void closeSerialPort();

    void on_send_button_clicked();

    void refresh_data(drone_data *data);

private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> port_list;
    QString selected_port;
    QSerialPort *serial;
    parser *parametry;
    QVector<double> time;
    QVector<double> yaw;
    QVector<double> pitch;
    QVector<double> roll;
    QVector<double> height;
    QVector<double> speed;
    QVector<double> battery;
    QElapsedTimer *timer;
    double min_h=100000;
    double max_h=-100000;
};

#endif // MAINWINDOW_H
