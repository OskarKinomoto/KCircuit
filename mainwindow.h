#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "mainwidget.h"
#include "objectsettingswidget.h"

#include "aboutdialog.h"

#include "enum.h"

#include "circuit.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

  inline static K::tool selectedTool(){return MainWindow::_selectedTool;}

private:
  //Main Widget
  void initMainWidget();
  MainWidget * mainWidget;
  //Actions
  void initActions();
  QAction * newFileAction;
  QAction * saveFileAction;
  QAction * saveFileAsAction;
  QAction * openFileAction;
  QAction * quitAction;

  QAction * mouseSelectAction;
  QAction * wireSelectAction;
  QAction * resistorSelectAction; ///TODO ofc~

  QAction * zoomInAction;
  QAction * zoomInAction2;
  QAction * zoomInAction3;
  QAction * zoomOutAction;
  QAction * showGridAction;

  QAction * aboutApplicationAction;

  //Menu
  void initMenus();
  QMenu * fileMenu;
  QMenu * editMenu;
  QMenu * viewMenu;
  QMenu * helpMenu;

  //Settings
  void loadSettings();
  void saveSettings();

  //Tool Bars
  void initToolBars();
  QToolBar * applicationBar;
  QToolBar * toolBar; // Toolbar with resistors etc
  QToolBar * objectSettingsBar;

  //Object settings
  void initObjectSettingsWidget();
  ObjectSettingsWidget * objectSettingsWidget;

  //Selected tool;
  static K::tool _selectedTool;
  void unselectLastUsed();

  //Dialogs
  void initDialogs();
  QFileDialog * openFileDialog;
  QFileDialog * saveFileDialog;
  QFileDialog * saveFileAsDialog;
  AboutDialog * aboutDialog;

protected:
  void closeEvent (QCloseEvent * event);

private slots:
  void newFile();
  void saveFile(QString file);
  void saveFileTest();
  void saveFileAs(QString file);
  void openFile(QString file);
  void quit();
  void wireSelect();
  void mouseSelect();
  void aboutApplication();
  void showGrid(bool b);
  void zoomIn();
  void zoomOut();
};

#endif // MAINWINDOW_H
