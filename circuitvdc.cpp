#include "circuitvdc.h"

#ifndef CONSTEXPR
float CircuitVDC::wspr = sqrt2;
#endif

CircuitVDC::CircuitVDC(Coordinate begin, float scale, quint16 rotation, quint32 num) : CircuitObject(rotation, num)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitVDC::CircuitVDC(QDataStream &in) : CircuitObject(in)
{

}

CircuitVDC::~CircuitVDC()
{

}

void CircuitVDC::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);
  p.drawEllipse(-1.5*gs,-1.5*gs,3*gs,3*gs);

  if(angle % 90)
    {
      p.drawLine(0, -1.5*gs, 0, -2*wspr*gs);
      p.drawLine(0, 1.5*gs, 0, 2*wspr*gs);

    }
  else
    {
      p.drawLine(0, -1.5*gs, 0, -3*gs);
      p.drawLine(0, 1.5*gs, 0, 3*gs);
    }
  p.drawLine(0, gs, 0, -gs);
  p.drawLine(-.3*gs, -.7*gs, 0, -gs);
  p.drawLine(.3*gs, -.7*gs, 0, -gs);
  p.restore();
}

bool CircuitVDC::save(QDataStream &out)
{
  out << quint32(K::Object::VDC);
  out << num;
  out << cords;
  out << angle;
  return true;
}

K::info CircuitVDC::info()
{

}

