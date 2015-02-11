#ifndef CIRCUITADC_H
#define CIRCUITADC_H

#include "circuitobject.h"

class CircuitADC : public CircuitObject
{
public:
  CircuitADC(Coordinate begin, float scale, quint16 rotation, quint32 num);
  CircuitADC(QDataStream& in);
  ~CircuitADC();
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
#endif // CIRCUITADC_H
