#include "circuitcoil.h"

#ifndef CONSTEXPR
  float CircuitCoil::wspr = sqrt2;
#endif

CircuitCoil::CircuitCoil(Coordinate begin, float scale, quint16 rotation) : CircuitObject(rotation)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitCoil::CircuitCoil(QDataStream &in) : CircuitObject(in)
{

}

CircuitCoil::~CircuitCoil()
{

}

void CircuitCoil::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);
  p.drawArc(-2.5*gs, -.75*gs, gs,1.5*gs, 0, 180*16);
  p.drawArc(-1.5*gs, -.75*gs, gs,1.5*gs, 0, 180*16);
  p.drawArc(-.5*gs, -.75*gs, gs,1.5*gs, 0, 180*16);
  p.drawArc(.5*gs, -.75*gs, gs,1.5*gs, 0, 180*16);
  p.drawArc(1.5*gs, -.75*gs, gs,1.5*gs, 0, 180*16);
    if(angle % 90)
      {
  p.drawLine(-2*wspr*gs,0,-2.5*gs,0);
  p.drawLine(2*wspr*gs,0,2.5*gs,0);
      }
    else
      {
        p.drawLine(-3*gs,0,-2.5*gs,0);
        p.drawLine(3*gs,0,2.5*gs,0);
      }
  p.restore();
}

bool CircuitCoil::save(QDataStream &out)
{
  out << quint32(K::Object::COIL);
  out << cords;
  out << angle;
  return true;
}

