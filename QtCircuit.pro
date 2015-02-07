#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T18:04:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCircuit
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    mainwidget.cpp \
    objectsettingswidget.cpp \
    aboutdialog.cpp \
    circuit.cpp \
    circuitscrollarea.cpp \
    circuitwidget.cpp \
    coordinate.cpp \
    abstractcircuitobject.cpp \
    circuitobject.cpp \
    circuitwire.cpp \
    circuitresistor.cpp \
    circuitcapacitor.cpp

HEADERS  += mainwindow.h \
    enum.h \
    mainwidget.h \
    objectsettingswidget.h \
    aboutdialog.h \
    circuit.h \
    circuitscrollarea.h \
    circuitwidget.h \
    coordinate.h \
    abstractcircuitobject.h \
    circuitobject.h \
    circuitwire.h \
    circuitresistor.h \
    circuitcapacitor.h

QMAKE_CXXFLAGS += -std=c++11
