#-------------------------------------------------
#
# Project created by QtCreator 2019-05-13T05:02:43
#
#-------------------------------------------------

QT       += core gui qml network quick positioning location serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = WDS_Dron
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += glm\
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 static

SOURCES += \
        comms.cpp \
        console.cpp \
        dialog.cpp \
        main.cpp \
        mainwindow.cpp \
        parser.cpp \
        pathcontroller.cpp \
        qcustomplot.cpp \
        texturedsphere.cpp

HEADERS += \
        comms.h \
        console.h \
        dialog.h \
        mainwindow.h \
        parser.h \
        pathcontroller.h \
        qcustomplot.h \
        texturedsphere.h

FORMS += \
        comms.ui \
        mainwindow.ui

LIBS += -lOpengl32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
