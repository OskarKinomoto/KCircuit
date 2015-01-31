#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>

#include "circuit.h"
#include "circuitscrollarea.h"

class MainWidget : public QWidget
{
  Q_OBJECT
public:
  explicit MainWidget(QWidget *parent = 0);
  ~MainWidget();

  int newTab( Circuit * circuit );

  void setMouseTrackingOnTabs(bool enable);
  void updateCurrent();
  inline CircuitScrollArea * getCurrent() { return (CircuitScrollArea*)tabWidget->currentWidget();}
  inline int currentIndex() { return tabWidget->currentIndex(); }

private:
  QVBoxLayout * vBox;
  QTabWidget * tabWidget;
  QWidget * statusBar;
  bool mouseTracking = false;

  void closeTabI(int i);
signals:

public slots:
  void closeTab(int i);
};

#endif // MAINWIDGET_H
