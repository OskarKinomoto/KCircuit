#include "objectcapacitor.h"
#include "textpainter.h"

ObjectCapacitor::ObjectCapacitor(QPoint p, quint16 a, quint32 id) : ObjectBase(p, a, K::COIL, id)
{
  name = "Capacitor " + QString::number(id);
}

ObjectCapacitor::ObjectCapacitor(QDataStream &in): ObjectBase(in, K::COIL)
{
  loadSettings(in);
}

ObjectCapacitor::~ObjectCapacitor()
{
  if(labelImg) delete labelImg;
}

bool ObjectCapacitor::isPointOverObject(QPointF p)
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

  if(x2 <= 3 && y2 <= .5) return true; /// REDO
  else if(x2 <= 2 && y2 <= 1) return true; /// REDO
  return false;
}

ObjectSettingsAbstract *ObjectCapacitor::settings(Circuit *)
{
  return nullptr;
}

QString ObjectCapacitor::getLabel() const
{
  return label;
}

void ObjectCapacitor::setLabel(const QString &value)
{
  label = value;
  gsRendered = 0;
}

ObjectCapacitor::TYPE ObjectCapacitor::getTyp() const
{
  return typ;
}

void ObjectCapacitor::setTyp(int value)
{
  typ = ObjectCapacitor::TYPE(value);
}

void ObjectCapacitor::drawObject(QPainter &p)
{
  p.drawLine(-.25*K::gs, K::gs, -.25*K::gs, -K::gs);
  p.drawLine(.25*K::gs, K::gs, .25*K::gs, -K::gs);

  if(angle % 90)
    {
      p.drawLine(-.25*K::gs, 0, -K::gs*K::sqrt2, 0);
      p.drawLine(.25*K::gs, 0, K::gs*K::sqrt2, 0);
    }
  else
    {
      p.drawLine(-.25*K::gs, 0, -K::gs, 0);
      p.drawLine(.25*K::gs, 0, K::gs, 0);
    }
}

void ObjectCapacitor::saveSettings(QDataStream &out)
{
  out << label;
  out << quint8(typ);
}

void ObjectCapacitor::loadSettings(QDataStream &in)
{
  in >> label;
  quint8 tmp;
  in >> tmp;
  typ = TYPE(tmp);
}
