#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T16:17:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp \
    tetrismodel.cpp \
    tetrisview.cpp \
    tetramino.cpp \
    tetriscontroller.cpp \
    tetrisfield.cpp \
    block.cpp \
    lcdwidget.cpp

HEADERS  += \
    tetrismodel.h \
    tetrisview.h \
    tetramino.h \
    tetriscontroller.h \
    tetrisfield.h \
    block.h \
    lcdwidget.h

FORMS    +=

#CONFIG += c++14

#QMAKE_CXXFLAGS += -std=gnu++14
