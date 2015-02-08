#include "circuitgenerator.h"

CircuitGenerator::CircuitGenerator(Coordinate begin, float scale, quint16 rotation) : CircuitObject(rotation)
{
  float gs = scale * grid;
  cords = Coordinate(begin.x() / gs + .5, begin.y() / gs + .5);
}

CircuitGenerator::CircuitGenerator(QDataStream &in) : CircuitObject(in)
{

}

CircuitGenerator::~CircuitGenerator()
{

}

void CircuitGenerator::draw(QPainter &p, float scale)
{
  float gs = scale * grid;
  p.save();
  if(drawing) p.setPen(Qt::gray);
  p.translate(cords.x() * gs, cords.y() * gs);
  p.rotate(this->angle);
  p.drawEllipse(-1.5*gs,-1.5*gs,3*gs,3*gs);
  p.drawLine(0, -1.5*gs, 0, -3*gs);
  p.drawLine(0, 1.5*gs, 0, 3*gs);

  //p.rotate(-this->angle);

  QPainterPath path;
  path.moveTo(-gs, 0);
  path.cubicTo(0, -2*gs, 0, 2*gs, gs, 0);

  p.drawPath(path);

  p.restore();
}

bool CircuitGenerator::save(QDataStream &out)
{
  out << quint32(K::Object::GENERATOR);
  out << cords;
  out << angle;
  return true;
}

