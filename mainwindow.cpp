#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : MainWindowView(parent), MainWindowModel()
{
  MainWindowView::init();
  connect(rotate45A, SIGNAL(triggered(bool)), this, SLOT(rotate45()));
  connect(rotate90A, SIGNAL(triggered(bool)), this, SLOT(rotate90()));
  connect(undoA, SIGNAL(triggered(bool)), this, SLOT(undo()));
  connect(redoA, SIGNAL(triggered(bool)), this, SLOT(redo()));
  connect(saveAllA, SIGNAL(triggered()), tabWidget, SLOT(saveAll()));
  connect(saveAsA, SIGNAL(triggered()), tabWidget, SLOT(saveAs()));
  connect(saveA, SIGNAL(triggered()), tabWidget, SLOT(save()));
  connect(openA, SIGNAL(triggered()), tabWidget, SLOT(open()));
  connect(newA, SIGNAL(triggered()), tabWidget, SLOT(newDefaultTab()));
  connect(zoomInA, SIGNAL(triggered()), tabWidget, SLOT(zoomIn()));
  connect(zoomIn2A, SIGNAL(triggered()), tabWidget, SLOT(zoomIn()));
  connect(zoomOutA, SIGNAL(triggered()), tabWidget, SLOT(zoomOut()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::leaveEvent(QEvent *event)
{

}

void MainWindow::enterEvent(QEvent *event)
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if(tabWidget->closeAllTab()) event->accept();
  else  event->ignore();
}

void MainWindow::rotate90()
{
  this->circuit()->rotate90();
}

void MainWindow::rotate45()
{
  this->circuit()->rotate45();
}

void MainWindow::undo()
{
  this->circuit()->undo();
}

void MainWindow::redo()
{
  this->circuit()->redo();
}
