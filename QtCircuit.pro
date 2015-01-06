#-------------------------------------------------
#
# Project created by QtCreator 2014-11-21T20:10:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCircuit
TEMPLATE = app


SOURCES += main.cpp\
        qtcircuitmain.cpp \
    kquitmodifiedbox.cpp \
    program.cpp \
    circuitwidget.cpp \
    settingswindow.cpp \
    circuitrenderarea.cpp \
    circuitscrollarea.cpp

HEADERS  += qtcircuitmain.h \
    kquitmodifiedbox.h \
    program.h \
    circuitwidget.h \
    settingswindow.h \
    circuitrenderarea.h \
    circuitscrollarea.h

QMAKE_CXXFLAGS += -std=c++11

TRANSLATIONS = QtCircuit_en_US.ts \
    QtCircuit_pl_PL.ts
CODECFORTR = UTF-8
