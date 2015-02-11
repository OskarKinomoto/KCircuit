#include "circuitcapacitor.h"

#ifndef CONSTEXPR
  float CircuitCapacitor::wspr = sqrt2;
#endif

CircuitCapacitor::~CircuitCapacitor()
{

}

void CircuitCapacitor::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);

  p.drawLine(-.25*gs, gs, -.25*gs, -gs);
  p.drawLine(.25*gs, gs, .25*gs, -gs);

  if(angle % 90)
    {
      p.drawLine(-.25*gs, 0, -gs*wspr, 0);
      p.drawLine(.25*gs, 0, gs*wspr, 0);
    }
  else
    {
      p.drawLine(-.25*gs, 0, -gs, 0);
      p.drawLine(.25*gs, 0, gs, 0);
    }
  p.restore();
}

bool CircuitCapacitor::save(QDataStream &out)
{
  out << quint32(K::Object::CAPACITOR);
  out << num;
  out << cords;
  out << angle;
  return true;
}

K::info CircuitCapacitor::info()
{

}



CircuitCapacitor::CircuitCapacitor(Coordinate begin, float scale, quint16 rotation, quint32 num) : CircuitObject(rotation, num)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitCapacitor::CircuitCapacitor(QDataStream &in) : CircuitObject(in)
{

}
