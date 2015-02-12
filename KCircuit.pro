#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T18:04:02
#
#-------------------------------------------------

QT       += core gui svg xml

win{
QT += winextras
#icony
# http://doc.qt.io/qt-5/qtwin.html#details
# https://stackoverflow.com/questions/6523039/qt-application-and-window-icon-under-windows
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KCircuit
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    mainwidget.cpp \
    aboutdialog.cpp \
    circuit.cpp \
    circuitscrollarea.cpp \
    circuitwidget.cpp \
    coordinate.cpp \
    abstractcircuitobject.cpp \
    circuitobject.cpp \
    circuitwire.cpp \
    circuitresistor.cpp \
    circuitcapacitor.cpp \
    circuitcoil.cpp \
    circuitvdc.cpp \
    circuitadc.cpp \
    circuitdiode.cpp \
    circuitgenerator.cpp \
    circuitopamp.cpp \
    infowidget.cpp \
    objectlistwidget.cpp \
    objectlistwidgetitem.cpp \
    circuithistory.cpp \
    abstracthistorynode.cpp \
    historynodenewobject.cpp \
    historynodedeleteobject.cpp

HEADERS  += mainwindow.h \
    include.h \
    mainwidget.h \
    aboutdialog.h \
    circuit.h \
    circuitscrollarea.h \
    circuitwidget.h \
    coordinate.h \
    abstractcircuitobject.h \
    circuitobject.h \
    circuitwire.h \
    circuitresistor.h \
    circuitcapacitor.h \
    circuitcoil.h \
    circuitvdc.h \
    circuitadc.h \
    circuitdiode.h \
    circuitgenerator.h \
    circuitopamp.h \
    infowidget.h \
    objectlistwidget.h \
    objectlistwidgetitem.h \
    circuithistory.h \
    abstracthistorynode.h \
    historynodenewobject.h \
    history.h \
    historynodedeleteobject.h

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc

RC_ICONS = app.ico
ICON = app.icns

DISTFILES +=
