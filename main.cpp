<<<<<<< HEAD
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
=======
#include "qtcircuitmain.h"
#include <QApplication>

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QCoreApplication::setApplicationName("QtCircuit");
  QCoreApplication::setOrganizationName("Kinomoto");
  QCoreApplication::setOrganizationDomain("kinomoto.me");


  // Own translation file
    QTranslator translator;
    translator.load(a.applicationName() + "_" + QLocale::system().name(), a.applicationDirPath());
    a.installTranslator(&translator);

    // Translation file for Qt stuff
    QTranslator translator2;
    translator2.load("qtbase_" + QLocale::system().name(), a.applicationDirPath());
    a.installTranslator(&translator2);

  QtCircuitMain w;
>>>>>>> 1fb822600bffa0763c7cb6dde836e243da585b22
  w.show();

  return a.exec();
}
