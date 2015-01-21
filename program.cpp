#include "program.h"



Program::Program(QtCircuitMain * main)
{
  window = main;
  pModified = false;

  QSettings settings;
  settings.beginGroup("MainWindow");
  window->resize(settings.value("size", QSize(400, 400)).toSize());
  window->move(settings.value("pos", QPoint(200, 200)).toPoint());
  settings.endGroup();
  settings.beginGroup("Program");
  settings.endGroup();
}

Program::~Program(){
  QSettings settings;
  settings.beginGroup("MainWindow");
  settings.setValue("size", window->size());
  settings.setValue("pos", window->pos());
  settings.endGroup();
  settings.beginGroup("SettingsWindow");
  settings.setValue("size", window->setwin->size());
  settings.setValue("pos", window->setwin->pos());
  settings.endGroup();
  settings.beginGroup("Program");
  settings.endGroup();
}
