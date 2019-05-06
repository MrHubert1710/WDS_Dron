#ifndef PARSER_H
#define PARSER_H
#include "ui_mainwindow.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

struct drone_data{
    double yaw; // rad
    double pitch; // rad
    double roll; // rad
    quint16 height; //m
    quint8 battery; //0-255 -> 0%-100%
    double speed; //m/s
    double lon;   // W-|+E
    double lat;   // S-|+N

};

class parser: public QObject
{
Q_OBJECT
public:
    parser();
signals:
    void dataChanged(drone_data *present);
public slots:
    void parseString(QString line);
private:
    drone_data *tmp;
};

#endif // PARSER_H
