#include "objectwire.h"

ObjectWire::ObjectWire(QPoint p, quint32 id) : ObjectAbstract(K::WIRE, id)
{
  QPoint tmp(p.x()/ K::gs + .5, p.y() / K::gs + .5);
  points.reserve(4);
  points.push_back(tmp);
  points.push_back(tmp);
}

ObjectWire::ObjectWire(QDataStream &in) : ObjectAbstract(K::WIRE, in)
{
  quint16 num;
  in >> num;
  points.reserve(num);
  for(int i = 0; i < num; ++i)
    {
      QPoint tmp;
      in >> tmp;
      points.push_back(tmp);
    }
  quint8 wmode;
  in >> wmode;
  mode = K::WIRE_MODE(wmode);
}

ObjectWire::~ObjectWire()
{

}

void ObjectWire::draw(QPainter &p)
{
  for(auto itr = points.begin(), itr2 = itr + 1; itr2 < points.end(); ++itr, ++itr2)
    p.drawLine(itr->x()*K::gs, itr->y()*K::gs, itr2->x()*K::gs, itr2->y()*K::gs);
}

void ObjectWire::save(QDataStream &out)
{
  out << quint32(K::WIRE);
  out << ID;
  out << quint16(points.size());
  for(QPoint& point : points)
    {
      out << point;
    }
}

bool ObjectWire::move(QPoint p)
{
  if(points.back() == p) return false;
  points.back() = p;
  return true;
}

bool ObjectWire::release()
{
  if(points[points.size() - 1] != points[points.size() - 2])
    points.push_back(points.back());
  return false;
}

bool ObjectWire::isPointOverObject(QPointF p)
{
  return false;
}

void ObjectWire::moveBy(QPoint d)
{

}

void ObjectWire::moveByGS(QPoint gs)
{

}

QPoint ObjectWire::acceptMove()
{
  return QPoint();
}

void ObjectWire::dropMove()
{

}

void ObjectWire::doubleClick()
{

}

ObjectSettingsAbstract *ObjectWire::settings(Circuit *c)
{
  return nullptr;
}

