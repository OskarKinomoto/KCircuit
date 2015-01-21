#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "qtcircuitmain.h"
#include <QMainWindow>

class QtCircuitMain;
class SettingsWindow;

class SettingsWindow_W1 : public QWidget
{
  Q_OBJECT

public:
  SettingsWindow_W1();

private:
  QLayout * layout;
  QCheckBox * t1;

private slots:
  void Ask(bool);
};

class SettingsWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit SettingsWindow(QtCircuitMain *parent = 0);

signals:

public slots:
private:
  QtCircuitMain * main;
  QWidget * central;
  QLayout * layout;
  QListWidget * list;
  QWidget * right;
  QStackedLayout * stacklayout;

  SettingsWindow_W1 * a;
  QWidget * b;

  QAction * aa;
  QAction * bb;
};

#endif // SETTINGSWINDOW_H
