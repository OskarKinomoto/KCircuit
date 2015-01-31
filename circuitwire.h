#ifndef CIRCUITWIRE_H
#define CIRCUITWIRE_H

#include <vector>

#include <QDebug>

#include "abstractcircuitobject.h"
#include "coordinate.h"


class CircuitWire : public AbstractCircuitObject
{
private:
  std::vector<Coordinate> cords;
  bool drawing;

public:
  CircuitWire(Coordinate begin, float scale);
  ~CircuitWire();

  virtual void draw(QPainter&p, float scale);
  virtual K::status mouseEvent(QMouseEvent * event, float scale);
  virtual K::status keyEvent(QKeyEvent * event, float scale);
};

#endif // CIRCUITWIRE_H
