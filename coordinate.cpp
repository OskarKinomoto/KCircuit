#include "coordinate.h"

Coordinate::Coordinate(QDataStream &in)
{
  in >> _x >> _y;
}

Coordinate::~Coordinate()
{

}



QDataStream &operator<<(QDataStream & out, const Coordinate & c)
{
  out << c._x << c._y;
  return out;
}
