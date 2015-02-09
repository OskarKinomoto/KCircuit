#ifndef CIRCUITVDC_H
#define CIRCUITVDC_H

#include "circuitobject.h"

class CircuitVDC : public CircuitObject
{
public:
  CircuitVDC(Coordinate begin, float scale, quint16 rotation);
  CircuitVDC(QDataStream& in);
  ~CircuitVDC();
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

#endif // CIRCUITVDC_H
