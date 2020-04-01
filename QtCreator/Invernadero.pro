#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T14:40:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Invernadero
TEMPLATE = app

CONFIG += extserialport

include(qextserialport-1.2rc/src/qextserialport.pri)

SOURCES += main.cpp\
           mainwindow.cpp\
           dialog.cpp \
    dialog2.cpp \
    dialog3.cpp

HEADERS  += mainwindow.h\
            dialog.h\
    dialog2.h \
    dialog3.h

FORMS    += mainwindow.ui\
            dialog.ui \
    dialog2.ui \
    dialog3.ui
