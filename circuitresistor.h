#ifndef CIRCUITRESISTOR_H
#define CIRCUITRESISTOR_H

#include "circuitobject.h"

class CircuitResistor : public CircuitObject
{
private:
  bool drawing = false;
public:
  CircuitResistor(Coordinate begin, float scale);
  CircuitResistor(QDataStream& in);
  ~CircuitResistor();

  virtual void draw(QPainter&p, float scale);
  virtual K::status mouseEvent(QMouseEvent * event, float scale);
  virtual K::status keyEvent(QKeyEvent * event, float scale);
  virtual bool save(QDataStream& out);
};

#endif // CIRCUITRESISTOR_H
