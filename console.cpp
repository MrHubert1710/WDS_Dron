#include "console.h"
#include <QTextBlock>
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

         if(data.data()[i]!='\x00'){
          if(data.data()[i] == '\n'){
            emit line_ready(last_line);
            //qDebug() << last_line;
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
    if(document()->blockCount()>400){
        QTextCursor cursor(document()->begin());
        cursor.select(QTextCursor::BlockUnderCursor);
        //qDebug()<<"Kasuje "<<document()->begin().text();
        cursor.removeSelectedText();
        cursor.deleteChar();
    }

    moveCursor(QTextCursor::End);
    insertPlainText(tmp);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}
