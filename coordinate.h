#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
public:
  Coordinate(int x = 0, int y = 0) : _x(x), _y(y) {}
  ~Coordinate();

  inline int x() { return _x; }
  inline int y() { return _y; }

  inline void setX(int x) { _x = x; }
  inline void setY(int y) { _y = y; }

  inline void operator+=(Coordinate& a) {_x += a._x; _y += a._y;}
  inline void operator-=(Coordinate& a) {_x -= a._x; _y -= a._y;}
  inline Coordinate operator+(Coordinate& a) {return Coordinate(_x + a._x, _y + a._y);}
  inline Coordinate operator-(Coordinate& a) {return Coordinate(_x - a._x, _y - a._y);}
  inline bool operator==(Coordinate& a) {return _x == a._x && _y == a._y;}
  inline bool operator!=(Coordinate& a) {return _x != a._x || _y != a._y;}

  inline Coordinate operator/(int s){return Coordinate(_x/s, _y/s);}

private:
  int _x;
  int _y;
};

#endif // COORDINATE_H
