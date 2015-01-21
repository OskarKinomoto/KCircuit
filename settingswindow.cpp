#include "settingswindow.h"

SettingsWindow_W1::SettingsWindow_W1() : QWidget(NULL){
  QSettings settings;
  settings.beginGroup("Program");


  layout = new QFormLayout(this);
  t1 = new QCheckBox(tr("t1"), this);
  t1->setCheckState(settings.value("askBeforeCloseWhenNotModified", true).toBool() ? Qt::Checked : Qt::Unchecked) ;

  connect(t1, SIGNAL(clicked(bool)), this, SLOT(Ask(bool)));

  settings.endGroup();
}

void SettingsWindow_W1::Ask(bool b){
  QSettings settings;
  settings.beginGroup("Program");
  settings.setValue("askBeforeCloseWhenNotModified", b);
  settings.endGroup();
}

SettingsWindow::SettingsWindow(QtCircuitMain *parent) :
  QMainWindow(NULL) /* change to parent if you want to always on top */
{
  main = parent;
  this->setWindowTitle(QCoreApplication::applicationName() + " – " + tr("Ustawienia"));
  QSettings settings;
  settings.beginGroup("SettingsWindow");
  this->resize(settings.value("size", QSize(400, 400)).toSize());
  this->move(settings.value("pos", QPoint(200, 200)).toPoint());
  settings.endGroup();

  central = new QWidget();
  layout = new QHBoxLayout();
  list = new QListWidget();
  right = new QWidget();
  stacklayout = new QStackedLayout();

  right->setLayout(stacklayout);
  this->setCentralWidget(central);
  central->setLayout(layout);

  new QListWidgetItem(QIcon::fromTheme("go-home"), tr("Ogólne"), list);
  new QListWidgetItem(tr("TODO"), list);

  a = new SettingsWindow_W1();
  //a->setLayout(new QGridLayout);
  //a->layout()->addWidget(new QLabel(tr("t")));
  b = new QLabel(tr("b"));
  stacklayout->addWidget(a);
  stacklayout->addWidget(b);
  layout->addWidget(list);
  layout->addWidget(right);
  list->setMaximumWidth(100);
  stacklayout->setCurrentWidget(a);

  connect(list, SIGNAL(currentRowChanged(int)), stacklayout, SLOT(setCurrentIndex(int)));

}
