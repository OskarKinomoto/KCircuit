#ifndef CIRCUITSCROLLAREA_H
#define CIRCUITSCROLLAREA_H

#include <QtWidgets>

#include "circuitwidget.h"

class CircuitScrollArea : public QScrollArea
{
  Q_OBJECT

public:
  CircuitScrollArea(Circuit * circuit, QWidget * parent);
  ~CircuitScrollArea();

  CircuitWidget * circuitWidget;

  void recolorScrollBars();
  void setMouseTrackingCircuit(bool enable);

protected:
  virtual void resizeEvent (QResizeEvent * event);
  virtual void wheelEvent(QWheelEvent * event);

private:
  QWidget * corner;
  decltype(QWheelEvent.delta()) delta = 0;

};

#endif // CIRCUITSCROLLAREA_H
