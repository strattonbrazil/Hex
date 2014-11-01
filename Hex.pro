#-------------------------------------------------
#
# Project created by QtCreator 2014-10-20T21:20:20
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    hexgrid.cpp \
    hex.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    hexgrid.h \
    hex.h

FORMS    += mainwindow.ui

RESOURCES += \
    assets.qrc
