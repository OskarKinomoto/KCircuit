#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSvg>

#include "mainwidget.h"
#include "objectsettingswidget.h"

#include "aboutdialog.h"

#include "include.h"

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
  QAction * exportToAction;
  QAction * quitAction;

  QAction * mouseSelectAction;
  QAction * wireSelectAction;
  QAction * resistorSelectAction;
  QAction * coilSelectAction;
  QAction * capacitorSelectAction;
  QAction * VDCSelectAction;
  QAction * ADCSelectAction;
  QAction * diodeSelectAction;
  QAction * generatorSelectAction;
  QAction * opAmpSelectAction;

  QAction * zoomInAction;
  QAction * zoomInAction2;
  QAction * zoomInAction3;
  QAction * zoomOutAction;
  QAction * showGridAction;
  QAction * rotateAction;
  QAction * smallRotateAction;

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

  //Fonts
  void initFonts();

protected:
  void closeEvent (QCloseEvent * event);
  void leaveEvent ( QEvent * event );
  void enterEvent ( QEvent * event );

private:
  bool mouseGrabRestore = false;

private slots:
  void newFile();
  void newFileInit();

  void saveFile();
  void saveFileAs();
  void openFile();

  void exportFile();

  void quit();

  void wireSelect();
  void mouseSelect();
  void resistorSelect();
  void coilSelect();
  void capacitorSelect();
  void VDCSelect();
  void ADCSelect();
  void diodeSelect();
  void generatorSelect();
  void opAmpSelect();

  void aboutApplication();
  void showGrid(bool b);
  void zoomIn();
  void zoomOut();
};

#endif // MAINWINDOW_H
