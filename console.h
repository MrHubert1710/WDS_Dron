#ifndef CONSOLE_H
#define CONSOLE_H

#include <QListWidget>
#include <string>

class Console : public QListWidget
{
Q_OBJECT
public:
    Console(QWidget *parent);
    void newItem(std::string string);
};

#endif // CONSOLE_H
