#ifndef CIRCUITDIODE_H
#define CIRCUITDIODE_H

#include "circuitobject.h"

class CircuitDiode : public CircuitObject
{
public:
  CircuitDiode(Coordinate begin, float scale, quint16 rotation);
  CircuitDiode(QDataStream& in);
  ~CircuitDiode();
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


#endif // CIRCUITDIODE_H
