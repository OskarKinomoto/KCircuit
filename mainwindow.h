#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "enum.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ///~MainWindow();

private:
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

  //Menu
  void initMenus();
  QMenu * fileMenu;
  QMenu * editMenu;

  //Settings
  void loadSettings();
  void saveSettings();

  //Tool Bars
  void initToolBars();
  QToolBar * toolBar; // Toolbar with resistors etc

  //Selected tool;
  K::tool selectedTool = K::MOUSE;
  void unselectLastUsed();

protected:
  void closeEvent (QCloseEvent * event);

private slots:
  void newFile();
  void saveFile();
  void saveFileAs();
  void openFile();
  void quit();
  void wireSelect();
  void mouseSelect();
};

#endif // MAINWINDOW_H
