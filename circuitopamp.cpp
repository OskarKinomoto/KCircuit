#include "circuitopamp.h"

CircuitOpAmp::CircuitOpAmp(Coordinate begin, float scale, quint16 rotation) : CircuitObject(rotation)
{
  float gs = scale * grid;
  if(rotation % 90) setAngle(rotation - 45);
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitOpAmp::CircuitOpAmp(QDataStream &in) : CircuitObject(in)
{

}

CircuitOpAmp::~CircuitOpAmp()
{

}

void CircuitOpAmp::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);
  p.drawLine(-2.5*gs, -2.5*gs, -2.5*gs, 2.5*gs);
  p.drawLine(-2.5*gs, -2.5*gs, 1.5*gs, 0);
  p.drawLine(-2.5*gs, 2.5*gs, 1.5*gs, 0);
  p.drawLine(2*gs, 0, 1.5*gs, 0);
  p.drawLine(-4*gs, -1*gs, -2.5*gs, -1*gs);
  p.drawLine(-4*gs, 1*gs, -2.5*gs, 1*gs);
  QFont f(p.font());
  f.setPixelSize(gs);
  p.setFont(f);
  p.drawText(-1.8*gs, 1.3*gs, "+");
  p.drawText(-1.8*gs, -0.7*gs, "-");

  p.restore();
}

bool CircuitOpAmp::save(QDataStream &out)
{
  out << quint32(K::Object::OPAMP);
  out << cords;
  out << angle;
  return true;
}

