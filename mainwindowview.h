#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include <QMainWindow>
#include <QtXml>
#include <QtSvg>

#include "global.h"
#include "tabwidget.h"

class MainWindowView : public QMainWindow
{
  Q_OBJECT
public:
  MainWindowView(QWidget *parent = 0);
  void init();
  ~MainWindowView();

protected: /** INITS **/
  void actionInit();
  void menuInit();
  void toolBarInit();
  void centralWidgetInit();
  void sizePositionInit();
  void keyPressEvent (QKeyEvent * event);

protected: /** VARIABLES **/

  /** ACTIONS **/
  QAction * newA;
  QAction * openA;
  QAction * saveA;
  QAction * saveAsA;
  QAction * saveAllA;
  QAction * exportA;
  QAction * quitA;

  QAction * zoomInA;
  QAction * zoomIn2A;
  QAction * zoomOutA;

  QAction * rotate90A;
  QAction * rotate45A;
  QAction * rotate270A;
  QAction * rotate315A;

  QAction * undoA;
  QAction * redoA;

  QAction * delA;

  /** MENUS **/
  QMenu * fileM;
  QMenu * editM;
  QMenu * viewM;

  /** TOOLBAR **/
  QToolBar * toolBar;

  /** ActionGroup - Wire type **/
  QActionGroup * ag;

  QAction * wireShortest;
  QAction * wireTaxi;

  /** CENTRAL WIDGET **/
  TabWidget * tabWidget;
};

#endif // MAINWINDOWVIEW_H
