#include "circuitwire.h"

CircuitWire::CircuitWire(Coordinate begin, float scale)
{
 float gs = scale * grid;
 Coordinate tmp(begin.x() / gs + .5, begin.y() / gs + .5);
 cords.push_back(tmp);
 cords.push_back(tmp);
 drawing = true;
}

CircuitWire::CircuitWire(QDataStream &in)
{
  quint16 t;
  in >> t;
  cords.reserve(t);
  for(int i = 0; i < t; ++i)
    {
      cords.push_back(Coordinate(in));
    }
}

CircuitWire::~CircuitWire()
{
}

void CircuitWire::draw(QPainter &p, float scale)
{
      float gs = scale * grid;
      for(auto itr = cords.begin(), itr2 = itr + 1; itr2 < cords.end(); ++itr, ++itr2)
        {
          p.drawLine(itr->x()*gs, itr->y()*gs, itr2->x()*gs, itr2->y()*gs);
        }

}

K::status CircuitWire::mouseEvent(QMouseEvent *event, float scale)
{
  float gs = scale * grid;
  Coordinate tmp(event->x()/gs + .5, event->y()/gs + .5);
  cords[cords.size() - 1] = tmp;
  if(event->button() == Qt::LeftButton && tmp != cords[cords.size() - 2])
    {
      cords.push_back(tmp);
    }

  return K::DRAWING;

}

K::status CircuitWire::keyEvent(QKeyEvent *event, float scale)
{
  auto key = event->key();
  if(key == Qt::Key_Enter || key == Qt::Key_Return)
    {
      cords.pop_back();
      return K::DRAWED;
    }
  else if(key == Qt::Key_Escape)
    {
      return K::DESTROY;
    }
  return K::DRAWING;
}

bool CircuitWire::save(QDataStream &out)
{
  // TYP
  out << quint32(K::Object::WIRE);
  out << quint16(cords.size());

  for(auto itr : cords)
    {
      out << itr;
    }

  return true;
}
