#ifndef CIRCUITDIODE_H
#define CIRCUITDIODE_H

#include "circuitobject.h"

class CircuitDiode : public CircuitObject
{
public:
  CircuitDiode(Coordinate begin, float scale, quint16 rotation, quint32 num);
  CircuitDiode(QDataStream& in);
  ~CircuitDiode();
  virtual void draw(QPainter&p, float scale);
  virtual bool save(QDataStream& out);
  virtual K::info info();
private:
#ifdef MATH_CONSTEXPR
  float constexpr static wspr = sqrt(2);
#elif defined(CONSTEXPR)
  float constexpr static wspr = sqrt2;
#else
  float static wspr;
#endif
};


#endif // CIRCUITDIODE_H
