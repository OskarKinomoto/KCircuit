#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "mainwidgetview.h"


class MainWidget : public MainWidgetView
{
  Q_OBJECT
public:
  MainWidget(CircuitSettings settings);
  MainWidget(QString path);
  ~MainWidget();
  void setIndex(int index);

protected:

private slots:
  void setPointer();
  void setWire();
  void setResistor();
  void setCoil();
  void setCapacitor();
private:
  void init();
};

#endif // MAINWIDGET_H
