#include "circuitobject.h"

void CircuitObject::normAngle()
{
  angle = angle % 360;
}

void CircuitObject::rotate()
{
  angle += 90;
  this->normAngle();
}

void CircuitObject::smallRotate()
{
  angle += 45;
  this->normAngle();
}

void CircuitObject::setAngle(qint16 a)
{
  while(a < 0) a += 360;
  angle = a;
  this->normAngle();
}

CircuitObject::CircuitObject(quint16 beginRotation)
{
  angle = beginRotation;
  this->normAngle();
  drawing = true;
}

K::status CircuitObject::mouseEvent(QMouseEvent *event, float scale)
{
  float gs = scale * grid;
  cords = Coordinate(event->x()/gs + .5, event->y()/gs + .5);
  if(event->button() == Qt::LeftButton)
    {
      drawing = false;
      return K::DRAWED;
    }
  return K::DRAWING;
}

CircuitObject::CircuitObject(QDataStream &in)
{
  cords = Coordinate(in);
  in >> angle;
}

CircuitObject::~CircuitObject()
{

}

