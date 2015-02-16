#include "objectresistor.h"

ObjectResistor::ObjectResistor(QPoint p, quint16 a, quint32 id) : ObjectBase(p, a, K::RESISTOR, id)
{
  name = "Resistor " + QString::number(id);
}

ObjectResistor::ObjectResistor(QDataStream &in) : ObjectBase(in, K::RESISTOR)
{

}

ObjectResistor::~ObjectResistor()
{

}

bool ObjectResistor::isPointOverObject(QPointF p)
{
  p /= K::gs;
  p -= point;
  float x = p.x();
  float y = p.y();
  auto d = K::degrees::angle2enum(angle);
  float x2 = x*K::degrees::cosine[d] + y*K::degrees::sine[d];
  float y2 = x*K::degrees::sine[d] - y*K::degrees::cosine[d];
  x2 = x2 < 0 ? -x2 : x2;
  y2 = y2 < 0 ? -y2 : y2;

  if(x2 <= 3 && y2 <= .5) return true;
  else if(x2 <= 2 && y2 <= 1) return true;
  return false;
}

void ObjectResistor::drawObject(QPainter &p)
{
  if(angle % 90) // angle = 45
    {
      p.drawLine(-2*K::sqrt2*K::gs, 0, -2*K::gs, 0);
      p.drawLine(2*K::sqrt2*K::gs, 0, 2*K::gs, 0);
    }
  else // angle = 90
    {
      p.drawLine(-3*K::gs, 0, -2*K::gs, 0);
      p.drawLine(3*K::gs, 0, 2*K::gs, 0);
    }
  p.drawRect(-2*K::gs, -.75*K::gs, 4*K::gs, 1.5*K::gs);
}

void ObjectResistor::saveSettings(QDataStream &out)
{

}

void ObjectResistor::loadSettings(QDataStream &in)
{

}

