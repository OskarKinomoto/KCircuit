#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  loadSettings();
  initActions();
  initMenus();
  initToolBars();
}

void MainWindow::initActions()
{
  //newFileAction
  newFileAction = new QAction(QIcon::fromTheme("document-new"), tr("&New..."), nullptr);
  newFileAction->setShortcut(QKeySequence::New);
  connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

  //openFileAction
  openFileAction = new QAction(QIcon::fromTheme("document-open"), tr("&Open"), nullptr);
  openFileAction->setShortcut(QKeySequence::Open);
  connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

  //saveFileAction
  saveFileAction = new QAction(QIcon::fromTheme("document-save"), tr("&Save"), nullptr);
  saveFileAction->setShortcut(QKeySequence::Save);
  connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

  //saveFileAsAction
  saveFileAsAction = new QAction(QIcon::fromTheme("document-save-as"), tr("Save as"), nullptr);
  saveFileAsAction->setShortcut(QKeySequence::SaveAs);
  connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

  //quitAction
  quitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Quit"), nullptr);
  quitAction->setShortcut(QKeySequence::Quit);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

  //mouseSelectAction
  mouseSelectAction = new QAction(QIcon::fromTheme("input-mouse"), tr("Mouse"), nullptr);
  mouseSelectAction->setCheckable(true);
  mouseSelectAction->setChecked(true);
  ///mouseSelectAction->setShortcut(QKeySequence::Quit);
  connect(mouseSelectAction, SIGNAL(triggered()), this, SLOT(mouseSelect()));

  //mouseSelectAction
  wireSelectAction = new QAction(QIcon::fromTheme("input-keyboard"), tr("Wire"), nullptr);
  wireSelectAction->setCheckable(true);
  ///wireSelectAction->setShortcut(QKeySequence::Quit);
  connect(wireSelectAction, SIGNAL(triggered()), this, SLOT(wireSelect()));
}

void MainWindow::initMenus()
{
  //fileMenu
  fileMenu = this->menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newFileAction);
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);
  fileMenu->addAction(saveFileAsAction);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);
}

void MainWindow::loadSettings()
{
  QSettings settings;
  settings.beginGroup("MainWindow");
  this->resize(settings.value("size", QSize(800, 600)).toSize());
  this->move(settings.value("pos", QPoint(200, 200)).toPoint());
  settings.endGroup();
}

void MainWindow::saveSettings()
{
  QSettings settings;
  settings.beginGroup("MainWindow");
  settings.setValue("size", this->size());
  settings.setValue("pos", this->pos());
  settings.endGroup();
}

void MainWindow::initToolBars()
{
  toolBar = new QToolBar(tr("Tool bar")); ///TODO nazwa :<
  toolBar->addAction(mouseSelectAction);
  toolBar->addAction(wireSelectAction);
  this->addToolBar(Qt::LeftToolBarArea, toolBar);
}

void MainWindow::unselectLastUsed()
{
  switch(selectedTool)
    {
      case K::MOUSE: mouseSelectAction->setChecked(false);
      break;

      case K::WIRE: wireSelectAction->setChecked(false);
      break;

    }
}

void MainWindow::newFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::saveFileAs()
{

}

void MainWindow::openFile()
{

}

void MainWindow::quit()
{
  saveSettings();
  QApplication::quit();
}


void MainWindow::wireSelect()
{
  unselectLastUsed();
  wireSelectAction->setChecked(true);
  selectedTool = K::WIRE;
}

void MainWindow::mouseSelect()
{
  unselectLastUsed();
  mouseSelectAction->setChecked(true);
  selectedTool = K::MOUSE;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    this->quit();
}


