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
  w.show();

  return a.exec();
}
