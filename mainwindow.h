#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
#include <QtXml>
#include <QtSvg>
**/

#include "mainwindowview.h"
#include "mainwindowmodel.h"

class MainWindow : public MainWindowView, public MainWindowModel {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

protected: /** REIMPLEMENTATIONS **/
  void leaveEvent(QEvent *event);
  void enterEvent(QEvent *event);
  void closeEvent(QCloseEvent *event);

  inline Circuit *circuit() { return tabWidget->circuit(); }

private slots:
  void rotate90();
  void rotate45();
  void rotate270();
  void rotate315();
  void undo();
  void redo();
  void del();
  void wireModeT();
  void wireModeS();
};

#endif // MAINWINDOW_H
