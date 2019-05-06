#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QListWidget>
#include <QBluetoothSocket>
#include <QString>
#include <QQuickView>
#include <QGuiApplication>
#include <QDebug>
#include <QTimer>
#include <QtBluetooth>
#include <string>
#include <cstdlib>
#include <QElapsedTimer>
#include "parser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();
signals:
    void dataArrived(QString line);
private slots:

    void on_progressBar_valueChanged(int value);

    void on_search_button_clicked();

    void on_connect_button_clicked();

    void on_send_button_clicked();

    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void on_dev_list_itemClicked(QListWidgetItem *item);
    void checkstatus_and_readline();
    void refresh_items (drone_data *data);

private:
    const QString serviceUuid=QStringLiteral("00001101-0000-1000-8000-00805F9B34FB");
    QTimer* m_timer; //Timer object for triggering updates
    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QString sel_device;
    QBluetoothSocket *socket;
    QString console_line;
    parser *new_parser;
    QVector<double> time;
    QVector<double> yaw;
    QVector<double> pitch;
    QVector<double> roll;
    QVector<double> height;
    QVector<double> speed;
    QVector<double> battery;
    QElapsedTimer timer;
    double min_h=100000;
    double max_h=-100000;
};

#endif // MAINWINDOW_H
