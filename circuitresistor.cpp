#include "circuitresistor.h"

CircuitResistor::CircuitResistor(Coordinate begin, float scale)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
  drawing = true;
}

CircuitResistor::CircuitResistor(QDataStream &in)
{
  cords = Coordinate(in);
}

CircuitResistor::~CircuitResistor()
{

}

void CircuitResistor::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  /// ROTATE~
  p.drawLine(-3*gs, 0, -2.5*gs, 0);
  p.drawLine(3*gs, 0, 2.5*gs, 0);
  p.drawLine(-2.5*gs, -gs, 2.5*gs, -gs);
  p.drawLine(-2.5*gs, gs, 2.5*gs, gs);
  p.drawLine(-2.5*gs, gs, -2.5*gs, -gs);
  p.drawLine(2.5*gs, gs, 2.5*gs, -gs);
  p.restore();
}

K::status CircuitResistor::mouseEvent(QMouseEvent *event, float scale)
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

K::status CircuitResistor::keyEvent(QKeyEvent *event, float)
{
  auto key = event->key();
  if(key == Qt::Key_Enter || key == Qt::Key_Return)
    {
      drawing = false;
      return K::DRAWED;
    }
  return K::DRAWING;
}

bool CircuitResistor::save(QDataStream &out)
{
  //TYP
  out << quint32(K::Object::RESISTOR);
  out << cords;
  return true;
}

