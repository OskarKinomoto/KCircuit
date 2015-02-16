#include "mainwindowmodel.h"
#include <QApplication>
#include <QStyle>
#include <QSettings>

MainWindowModel::MainWindowModel()
{
  globalInit();

#ifdef QT_DEBUG
  if(!K::oxygen.exactMatch())
    qWarning() << "Oxygen is not loaded.";
#endif
}

MainWindowModel::~MainWindowModel()
{
  K::pointerI = QIcon();
  K::resistorI = QIcon();
}

void MainWindowModel::globalInit()
{
  QSettings set;
  QFontDatabase::addApplicationFont(":/fonts/oxygen.otf");
  K::oxygen = QFont("oxygen");
  K::breeze = QApplication::style()->objectName() == "breeze";
  K::grid = set.value("gridSize", 20).toInt();

  K::pointerI = QIcon(":/icons/pointer.svg");
  K::resistorI = QIcon(":/icons/R.svg");
  K::home = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

