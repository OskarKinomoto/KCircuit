#include "mainwindowmodel.h"
#include <QApplication>
#include <QStyle>
#include <QSettings>
#include <QFontMetrics>
#include <QColor>

MainWindowModel::MainWindowModel() {
  globalInit();

#ifdef QT_DEBUG
  if (!K::oxygen.exactMatch())
    qWarning() << "Oxygen is not loaded.";
#endif
}

MainWindowModel::~MainWindowModel() {
  K::pointerI = QIcon();
  K::wireI = QIcon();
  K::wireTaxiI = QIcon();
  K::wireShortestI = QIcon();
  K::resistorI = QIcon();
  K::capacitorI = QIcon();
  K::coilI = QIcon();
}

void MainWindowModel::globalInit() {
  QSettings set;
  QFontDatabase::addApplicationFont(":/fonts/oxygen.otf");
  K::oxygen = QFont("oxygen");
  QFontMetrics fm(K::oxygen);
  K::oxygenHeight = fm.height();
  K::oxygenAscent = fm.ascent();
  K::oxygenDescent = fm.descent();
  K::breeze = QApplication::style()->objectName() == "breeze";
  K::grid = set.value("gridSize", 20).toInt();

  K::pointerI = QIcon(":/icons/pointer.svg");
  K::wireI = QIcon(":/icons/wire.svg");
  K::wireTaxiI = QIcon(":/icons/wire_taxi");
  K::wireShortestI = QIcon(":/icons/wire_shortest");
  K::resistorI = QIcon(":/icons/R.svg");
  K::capacitorI = QIcon(":/icons/C.svg");
  K::coilI = QIcon(":/icons/L.svg");
  K::home = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

  K::baseC = QColor::fromRgb(77, 77, 77);
}
