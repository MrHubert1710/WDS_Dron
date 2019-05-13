#include "console.h"
#include <QDebug>
Console::Console(QWidget *parent): QTextEdit(parent)
{
    setReadOnly(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QPalette p;
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    new_recieve = true;
}

void Console::putData(const QByteArray &data,bool sending)
{
    QByteArray tmp(data);
    if(!sending){
        for(int i=0;i<data.size();++i){
          if(data.data()[i] == '\n'){
            emit line_ready(last_line);
            qDebug() << last_line;
            last_line.clear();
          }else{
            last_line.append(data.data()[i]);
          }

          if(new_recieve){
              tmp.insert(i,">> ");
              new_recieve=false;
          }else{
              if(data.data()[i] == '\n')
                  new_recieve=true;
          }

        }
    }else{
        for(int i=0;i<data.size();++i){
            if(new_recieve){
                tmp.insert(i,"<< ");
                new_recieve=false;
            }else{
                if(data.data()[i] == '\n')
                    new_recieve=true;
            }

        }
    }
    moveCursor(QTextCursor::End);
    insertPlainText(tmp);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}
/*
void Console::newItem(std::string string)
{
    //QListWidgetItem *item = new QListWidgetItem;
    //item->setText(string);
    //qDebug() << string.c_str();
    if(string.size()!=2){
        addItem(string.c_str());
    }
}
*/
