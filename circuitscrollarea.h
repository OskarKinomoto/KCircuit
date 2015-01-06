#ifndef CIRCUITSCROLLAREA_H
#define CIRCUITSCROLLAREA_H

#include <QtWidgets>
#include "circuitrenderarea.h"

class CircuitScrollArea : public QScrollArea
{
  Q_OBJECT
public:
  CircuitScrollArea();
  ~CircuitScrollArea();

protected:
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
};

#endif // CIRCUITSCROLLAREA_H
