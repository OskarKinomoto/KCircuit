#ifndef CIRCUITOBJECT_H
#define CIRCUITOBJECT_H

#include "abstractcircuitobject.h"

class CircuitObject : public AbstractCircuitObject
{
private:
  void normAngle();
protected:
  Coordinate cords;
  quint16 angle = 0;

  bool drawing = false;

  void rotate();
  void smallRotate();
  void setAngle(qint16 a);
  virtual K::status doubleClick() { return K::DRAWING;}
public:
  CircuitObject(quint16 beginRotation);
  CircuitObject(QDataStream& in);
  virtual K::status mouseEvent(QMouseEvent * event, float scale);
  virtual ~CircuitObject();
};

#endif // CIRCUITOBJECT_H
