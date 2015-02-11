#include "circuitdiode.h"

#ifndef CONSTEXPR
  float CircuitDiode::wspr = sqrt2;
#endif

CircuitDiode::CircuitDiode(Coordinate begin, float scale, quint16 rotation, quint32 num) : CircuitObject(rotation, num)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitDiode::CircuitDiode(QDataStream &in) : CircuitObject(in)
{

}

CircuitDiode::~CircuitDiode()
{

}

void CircuitDiode::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);

  p.drawLine(-.75*gs, -gs, -.75*gs, gs);
  p.drawLine(.75*gs, -gs, .75*gs, gs);

  p.drawLine(-.75*gs, -gs, .75*gs, 0);
  p.drawLine(-.75*gs, gs, .75*gs, 0);

  if(angle % 90)
    {
      p.drawLine(-.75*gs, 0, -2*wspr*gs, 0);
      p.drawLine(.75*gs, 0, 2*wspr*gs, 0);

    }
  else
    {
      p.drawLine(-.75*gs, 0, -2*gs, 0);
      p.drawLine(.75*gs, 0, 2*gs, 0);
    }
  p.restore();
}

bool CircuitDiode::save(QDataStream &out)
{
  out << quint32(K::Object::DIODE);
  out << num;
  out << cords;
  out << angle;
  return true;
}

K::info CircuitDiode::info()
{
  return {K::Object::DIODE, QString("Diode ") + QString::number(num), this};
}

