#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : MainWindowView(parent), MainWindowModel()
{
  MainWindowView::init();
  connect(rotate45A, &QAction::triggered, this, &MainWindow::rotate45);
  connect(rotate90A, &QAction::triggered, this, &MainWindow::rotate90);
  connect(rotate315A, &QAction::triggered, this, &MainWindow::rotate315);
  connect(rotate270A, &QAction::triggered, this, &MainWindow::rotate270);
  connect(undoA, &QAction::triggered, this, &MainWindow::undo);
  connect(redoA, &QAction::triggered, this, &MainWindow::redo);
  connect(saveAllA, &QAction::triggered, tabWidget, &TabWidget::saveAll);
  connect(saveAsA, &QAction::triggered, tabWidget, &TabWidget::saveAs);
  connect(saveA, &QAction::triggered, tabWidget, &TabWidget::save);
  connect(openA, &QAction::triggered, tabWidget, &TabWidget::open);
  connect(newA, &QAction::triggered, tabWidget, &TabWidget::newDefaultTab);
  connect(zoomInA, &QAction::triggered, tabWidget, &TabWidget::zoomIn);
  connect(zoomIn2A, &QAction::triggered, tabWidget, &TabWidget::zoomIn);
  connect(zoomOutA, &QAction::triggered, tabWidget, &TabWidget::zoomOut);
  connect(delA, &QAction::triggered, this, &MainWindow::del);
  connect(wireTaxi, &QAction::triggered, this, &MainWindow::wireModeT);
  connect(wireShortest, &QAction::triggered, this, &MainWindow::wireModeS);
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

void MainWindow::rotate270()
{
  this->circuit()->rotate270();
}

void MainWindow::rotate315()
{
  this->circuit()->rotate315();
}

void MainWindow::undo()
{
  this->circuit()->undo();
}

void MainWindow::redo()
{
  this->circuit()->redo();
}

void MainWindow::del()
{
  this->circuit()->removeCurrent();
}

void MainWindow::wireModeT()
{
  K::wireMode = K::WIRE_TAXI;
}

void MainWindow::wireModeS()
{
  K::wireMode = K::WIRE_SHORTEST;
}
