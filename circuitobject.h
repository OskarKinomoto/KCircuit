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

  void virtual rotate();
  void virtual smallRotate();
  virtual bool isSmallRotate() { return true; }
  void setAngle(qint16 a);
  virtual K::status doubleClick() { return K::DRAWING;}
public:
  CircuitObject(quint16 beginRotation, quint32 num);
  CircuitObject(QDataStream& in);
  virtual K::status mouseEvent(QMouseEvent * event, float scale);
  virtual ~CircuitObject();
  virtual bool isDrawing() { return drawing; }
};

#endif // CIRCUITOBJECT_H
