#ifndef CIRCUITCOIL_H
#define CIRCUITCOIL_H


#include "circuitobject.h"

class CircuitCoil : public CircuitObject
{
public:
  CircuitCoil(Coordinate begin, float scale, quint16 rotation);
  CircuitCoil(QDataStream& in);
  ~CircuitCoil();

  virtual void draw(QPainter&p, float scale);
  virtual bool save(QDataStream& out);
private:
#ifdef MATH_CONSTEXPR
  float constexpr static wspr = sqrt(2);
#elif defined(CONSTEXPR)
  float constexpr static wspr = sqrt2;
#else
  float static wspr;
#endif
};

#endif // CIRCUITCOIL_H
