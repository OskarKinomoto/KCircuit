#ifndef QTCIRCUITMAIN_H
#define QTCIRCUITMAIN_H

#include <QMainWindow>
#include <QtWidgets>
#include "kquitmodifiedbox.h"
#include "program.h"
#include "circuitwidget.h"
#include "settingswindow.h"

class Program;
class SettingsWindow;

class QtCircuitMain : public QMainWindow
{
  Q_OBJECT

private:
  Program * prog;
  friend class Program;
  QMenu * menuFile;
  QMenu * menuEdit;


  //Init actions
  void initActions();
  //Actions
  QAction * quitAct;
  QAction * newAct;
  QAction * saveAct;
  QAction * saveasAct;
  QAction * openAct;
  QAction * openPrefAct;

  //Actions resistor etc.
  QAction * mouseAct;

  KQuitModifiedBox * QuitModifiedBox;
  QFileDialog * fileDialog;

  QBoxLayout * CenterLayout;
  QTabWidget * Tabs;

  void initToolbar();
  QToolBar * toolbar;
  void initToolbarItems();
  QToolBar * toolbarItems;

  //Kontener na circuit widget
  std::map<int, CircuitWidget*> kontener;

  //Settings Window
  SettingsWindow * setwin;

  void initMenu();

  void newTab();

protected:
  void closeEvent (QCloseEvent * event);

private slots:
  void Quit();
  void Save();
  void Open();
  void New();
  void OpenPref();

public:
  QtCircuitMain(QWidget *parent = 0);
  ~QtCircuitMain();
};

#endif // QTCIRCUITMAIN_H
