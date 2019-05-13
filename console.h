#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>
#include <QScrollBar>
class Console : public QTextEdit
{
Q_OBJECT
private:
    bool new_recieve;
public:
    QByteArray last_line;
    Console(QWidget *parent);
    void putData(const QByteArray &data,bool sending);
signals:
    void line_ready(QByteArray dane);
};

#endif // CONSOLE_H
