#include "circuitresistor.h"

#ifndef CONSTEXPR
  float CircuitResistor::wspr = 2*sqrt2;
#endif

CircuitResistor::CircuitResistor(Coordinate begin, float scale, quint16 rotation) : CircuitObject(rotation)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitResistor::CircuitResistor(QDataStream &in) : CircuitObject(in)
{

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
  p.rotate(this->angle);
  if(angle % 90)
    {
      p.setRenderHint(QPainter::Antialiasing);
      p.drawLine(-wspr*gs, 0, -2*gs, 0);
      p.drawLine(wspr*gs, 0, 2*gs, 0);
    }
  else
    {
      p.drawLine(-3*gs, 0, -2*gs, 0);
      p.drawLine(3*gs, 0, 2*gs, 0);
    }
  p.drawLine(-2*gs, -.75*gs, 2*gs, -.75*gs);
  p.drawLine(-2*gs, .75*gs, 2*gs, .75*gs);
  p.drawLine(-2*gs, .75*gs, -2*gs, -.75*gs);
  p.drawLine(2*gs, .75*gs, 2*gs, -.75*gs);
  p.restore();
}

bool CircuitResistor::save(QDataStream &out)
{
  //TYP
  out << quint32(K::Object::RESISTOR);
  out << cords;
  out << angle;
  return true;
}

