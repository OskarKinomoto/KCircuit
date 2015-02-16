#ifndef MAINWIDGETVIEW_H
#define MAINWIDGETVIEW_H

#include <QWidget>
#include <QLabel>
#include <QToolBar>

#include "circuit.h"
#include "statusbar.h"
#include "scrollarea.h"
#include "rightwidget.h"

class MainWidgetView : public QWidget
{
  Q_OBJECT
public:
  explicit MainWidgetView(CircuitSettings settings, QWidget *parent = 0);
  explicit MainWidgetView(QString path, QWidget *parent = 0);
  virtual ~MainWidgetView();

public:
  Circuit * circuit;
protected:
  StatusBar * statusBar;

  QToolBar * toolBar;
  RightWidget * rightWidget;
public:
  ScrollArea * scroll;

private:
  void initView();
  void initToolbar();

  QActionGroup * ac;
protected:
  QAction * selectA;
  QAction * resistorA;
private:
  QVBoxLayout * vBox;
  QHBoxLayout * hBox;
  QWidget * layoutCointerner;

signals:

public slots:
};

#endif // MAINWIDGETVIEW_H
