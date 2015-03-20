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
    mainwindowview.cpp \
    global.cpp \
    mainwidgetview.cpp \
    mainwidget.cpp \
    tabwidgetview.cpp \
    tabwidget.cpp \
    circuitview.cpp \
    circuitmodel.cpp \
    circuit.cpp \
    mainwindowmodel.cpp \
    objectabstract.cpp \
    statusbar.cpp \
    scrollarea.cpp \
    objectbase.cpp \
    objectresistor.cpp \
    circuitdata.cpp \
    history.cpp \
    historynodeabstract.cpp \
    historynodenew.cpp \
    rightwidgetview.cpp \
    rightwidget.cpp \
    listobjects.cpp \
    listobjectsitem.cpp \
    historynoderemove.cpp \
    historynoderotate.cpp \
    historynodemove.cpp \
    objectsettingsabstract.cpp \
    objectsettingsresistor.cpp \
    textpainter.cpp \
    colorcombobox.cpp \
    objectwire.cpp \
    objectcapacitor.cpp \
    objectcoil.cpp

HEADERS  += mainwindow.h \
    mainwindowview.h \
    global.h \
    mainwidgetview.h \
    mainwidget.h \
    tabwidgetview.h \
    tabwidget.h \
    circuitview.h \
    circuitmodel.h \
    circuit.h \
    mainwindowmodel.h \
    objectabstract.h \
    objects.h \
    statusbar.h \
    scrollarea.h \
    circuitsettings.h \
    objectbase.h \
    objectresistor.h \
    circuitdata.h \
    tools.h \
    history.h \
    historynodeabstract.h \
    historynodenew.h \
    rightwidgetview.h \
    rightwidget.h \
    listobjects.h \
    listobjectsitem.h \
    historynoderemove.h \
    historynoderotate.h \
    historynodemove.h \
    objectsettingsabstract.h \
    objectsettingsresistor.h \
    textpainter.h \
    colorcombobox.h \
    objectwire.h \
    objectcapacitor.h \
    objectcoil.h

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc

RC_ICONS = app.ico
ICON = app.icns

DISTFILES +=
