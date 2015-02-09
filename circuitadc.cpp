#include "circuitadc.h"


#ifndef CONSTEXPR
  float CircuitADC::wspr = sqrt2;
#endif


CircuitADC::CircuitADC(Coordinate begin, float scale, quint16 rotation) : CircuitObject(rotation)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitADC::CircuitADC(QDataStream &in) : CircuitObject(in)
{

}

CircuitADC::~CircuitADC()
{

}

void CircuitADC::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);
  p.drawEllipse(-1.5*gs,-1.5*gs,3*gs,3*gs);
  p.drawEllipse(-1.25*gs,-1.25*gs,2.5*gs,2.5*gs);

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

  p.drawLine(0, .9*gs, 0, -.9*gs);
  p.drawLine(-.3*gs, -.6*gs, 0, -.9*gs);
  p.drawLine(.3*gs, -.6*gs, 0, -.9*gs);
  p.restore();
}

bool CircuitADC::save(QDataStream &out)
{
  out << quint32(K::Object::ADC);
  out << cords;
  out << angle;
  return true;
}

