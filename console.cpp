#include "console.h"
#include <QDebug>
Console::Console(QWidget *parent): QListWidget(parent)
{

}

void Console::newItem(std::string string)
{
    //QListWidgetItem *item = new QListWidgetItem;
    //item->setText(string);
    //qDebug() << string.c_str();
    if(string.size()!=2){
        addItem(string.c_str());
    }
}
