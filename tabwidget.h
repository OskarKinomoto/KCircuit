#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "tabwidgetview.h"
#include "mainwidget.h"
#include "global.h"

class TabWidget : public TabWidgetView {
  Q_OBJECT
public:
  TabWidget();
  ~TabWidget();

  void setName(QString name, int index);
  Circuit *circuit();

  void changeTitle(QString title, int index);

public slots:
  void newDefaultTab();
  void newTab(QString path);
  bool save();
  void saveAs();
  void saveAll();
  void open();
  bool closeTab(int i, bool *saveAll = new bool(false), bool close = false);
  bool closeAllTab();
  void zoomIn();
  void zoomOut();

private slots:
  void tabMoved(int, int);

private:
  void updateIndex();
};

#endif // TABWIDGET_H
