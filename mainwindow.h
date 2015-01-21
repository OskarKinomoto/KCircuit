#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  //Actions
  void initActions();
  QAction * newFileAction;
  QAction * saveFileAction;
  QAction * saveFileAsAction;
  QAction * openFileAction;

  //Menu
  void initMenus();
  QMenu * fileMenu;
  QMenu * editMenu;

private slots:
  void newFile();
  void saveFile();
  void saveFileAs();
  void openFile();
};

#endif // MAINWINDOW_H
