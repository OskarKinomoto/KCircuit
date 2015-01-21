#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  initActions();
  initMenus();
}

MainWindow::~MainWindow()
{

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
}

void MainWindow::initMenus()
{
  //fileMenu
  fileMenu = this->menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newFileAction);
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);
  fileMenu->addAction(saveFileAsAction);
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


