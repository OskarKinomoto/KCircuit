#ifndef COORDINATE_H
#define COORDINATE_H

#include <QDataStream>

class Coordinate
{
public:
  Coordinate(qint16 x = 0, qint16 y = 0) : _x(x), _y(y) {}
  Coordinate(QDataStream& in);
  ~Coordinate();

  inline qint16 x() { return _x; }
  inline qint16 y() { return _y; }

  inline void setX(qint16 x) { _x = x; }
  inline void setY(qint16 y) { _y = y; }

  inline void operator+=(Coordinate& a) {_x += a._x; _y += a._y;}
  inline void operator-=(Coordinate& a) {_x -= a._x; _y -= a._y;}
  inline Coordinate operator+(Coordinate& a) {return Coordinate(_x + a._x, _y + a._y);}
  inline Coordinate operator-(Coordinate& a) {return Coordinate(_x - a._x, _y - a._y);}
  inline bool operator==(Coordinate& a) {return _x == a._x && _y == a._y;}
  inline bool operator!=(Coordinate& a) {return _x != a._x || _y != a._y;}

  inline Coordinate operator/(float s){return Coordinate(_x/s, _y/s);}

  friend QDataStream &operator<<(QDataStream &, const Coordinate &);

private:
  qint16 _x;
  qint16 _y;
};



#endif // COORDINATE_H
