#include "objectbase.h"

ObjectBase::ObjectBase(QPoint p, quint16 a, K::objectType t, quint32 id) : ObjectAbstract(t, id)
{
  point = QPoint(p.x()/ K::gs + .5, p.y() / K::gs + .5);
  angle = a;
}

ObjectBase::ObjectBase(QDataStream &in, K::objectType t) : ObjectAbstract(t, in)
{
  in >> point;
  in >> angle;
  in >> name;
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::draw(QPainter &p)
{
  p.save();
  p.translate(point * K::gs);
  p.rotate(angle);
  drawObject(p);
  p.restore();
}

void ObjectBase::save(QDataStream &out)
{
  out << (quint32) this->type;
  out << ID;
  out << point;
  out << angle;
  out << name;
  saveSettings(out);
}

bool ObjectBase::move(QPoint p)
{
  p = QPoint(p.x()/ K::gs + .5, p.y() / K::gs + .5);
  if(point == p) return false;
  point = p; return true;
}

bool ObjectBase::release()
{
  return true;
}

bool ObjectBase::rotate45()
{
  angle += 45;
  angle %= 360;
  return true;
}

bool ObjectBase::rotate90()
{
  angle += 90;
  angle %= 360;
  return true;
}

