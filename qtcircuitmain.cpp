#include "qtcircuitmain.h"

QtCircuitMain::QtCircuitMain(QWidget *parent)
  : QMainWindow(parent)
{
  prog = new Program(this);
  setwin = new SettingsWindow(this);

  initActions();

  Tabs = new QTabWidget();

  this->setCentralWidget(Tabs);


  initMenu();
  initToolbar();
  initToolbarItems();

  QuitModifiedBox = new KQuitModifiedBox;

  fileDialog = new QFileDialog(this);
  QStringList fileList;
  fileList << "QtCircuit (*.qtc)" << tr("All filest (*.*)");
  fileDialog->setNameFilters(fileList);
  fileDialog->setDefaultSuffix(QString(".qtc"));

  //tmp
  newTab();
}

void QtCircuitMain::initToolbarItems(){
  toolbarItems = new QToolBar(tr("Elementy"));
  //toolbarItems->setMovable(false);

  toolbarItems->addAction(mouseAct);

  this->addToolBar(Qt::LeftToolBarArea, toolbarItems);
}

void QtCircuitMain::initMenu(){
  menuFile = this->menuBar()->addMenu(tr("&Plik"));
  menuFile->addAction(newAct);
  menuFile->addAction(openAct);
  menuFile->addAction(saveAct);
  menuFile->addAction(saveasAct);
  menuFile->addSeparator();
  menuFile->addAction(quitAct);

  menuEdit = this->menuBar()->addMenu(tr("&Edycja"));
  menuEdit->addSeparator();
  menuEdit->addAction(openPrefAct);
}

void QtCircuitMain::initToolbar(){
  toolbar = new QToolBar(tr("Podstawowy"));
  //toolbar->setMovable(false);

  toolbar->addAction(newAct);
  toolbar->addAction(saveAct);
  toolbar->addAction(openAct);
  toolbar->addSeparator();

  this->addToolBar(Qt::TopToolBarArea, toolbar);
}

QtCircuitMain::~QtCircuitMain()
{
  delete prog;
}

void QtCircuitMain::initActions(){
  quitAct = new QAction(QIcon::fromTheme("application-exit"), tr("&Zakończ"), NULL);
  quitAct->setShortcut(QKeySequence::Quit);
  connect(quitAct, SIGNAL(triggered()), this, SLOT(Quit()));

  newAct = new QAction(QIcon::fromTheme("document-new"), tr("&Nowy"), NULL);
  newAct->setShortcut(QKeySequence::New);
  connect(newAct, SIGNAL(triggered()), this, SLOT(New()));

  openAct = new QAction(QIcon::fromTheme("document-open"), tr("&Otwórz"), NULL);
  openAct->setShortcut(QKeySequence::Open);
  connect(openAct, SIGNAL(triggered()), this, SLOT(Open()));

  saveAct = new QAction(QIcon::fromTheme("document-save"), tr("&Zapisz"), NULL);
  saveAct->setShortcut(QKeySequence::Save);
  connect(saveAct, SIGNAL(triggered()), this, SLOT(Save()));

  saveasAct = new QAction(QIcon::fromTheme("document-save-as"), tr("Z&apisz jako"), NULL);
  saveasAct->setShortcut(QKeySequence::SaveAs);
  connect(saveasAct, SIGNAL(triggered()), this, SLOT(Save()));

  openPrefAct = new QAction(QIcon::fromTheme("preferences-other"), tr("Preferencje"), NULL);
  connect(openPrefAct, SIGNAL(triggered()), this, SLOT(OpenPref()));

  mouseAct = new QAction(QIcon::fromTheme("input-mouse"), tr("Myszka"), NULL);
}

void QtCircuitMain::OpenPref(){
  ///TODO
  setwin->show();
  setwin->raise();
  setwin->activateWindow();
}

void QtCircuitMain::closeEvent (QCloseEvent * event){
  QSettings settings;
  settings.beginGroup("Program");
  if(prog->modified()){
      //zmodyfikowany
      switch(QuitModifiedBox->exec()){
        case QMessageBox::Save:
          //prog->save();
          event->accept();
          break;

        case QMessageBox::Discard:
          event->accept();
          break;

        case QMessageBox::Cancel:
          event->ignore();
          break;
        }
  }  else if(settings.value("askBeforeCloseWhenNotModified", true).toBool()) {
      //nie zmodyfikowany
      if(QMessageBox::question(this, tr("Zakończ"), tr("Zakończ?"),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
          event->accept();
        } else {
          event->ignore();
        }
  } else {
      event->accept();
    }
}

void QtCircuitMain::newTab(){
  CircuitWidget * tmp = new CircuitWidget();
  int i = Tabs->addTab(tmp, tr("tak")); /** TAK? */
  Tabs->setTabText(i, tr("Tab %n", "", i+1));
  Tabs->setCurrentIndex(i);
}

void QtCircuitMain::Quit(){
  this->close();
}

void QtCircuitMain::New(){
  this->newTab();
}

void QtCircuitMain::Open(){
  fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog->exec();
}

void QtCircuitMain::Save(){
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->exec();
}
