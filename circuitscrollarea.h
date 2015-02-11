#ifndef CIRCUITSCROLLAREA_H
#define CIRCUITSCROLLAREA_H

#include <QtWidgets>

#include "circuitwidget.h"

class CircuitScrollArea : public QScrollArea
{
  Q_OBJECT

public:
  CircuitScrollArea(Circuit * circuit, QTabWidget * parent);
  ~CircuitScrollArea();

  CircuitWidget * circuitWidget;

  void recolorScrollBars();
  void setMouseTrackingCircuit(bool enable);
  void setTitle(QString s);
  void inline center(){ circuitWidget->centering(); }



protected:
  virtual void resizeEvent (QResizeEvent * event);
  virtual void wheelEvent(QWheelEvent * event);

private:
#ifdef __linux__
  QWidget * corner = nullptr;
#endif
  QTabWidget * parentTabWidget;
  int delta = 0;

};

#endif // CIRCUITSCROLLAREA_H
