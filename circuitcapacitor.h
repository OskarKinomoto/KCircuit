#ifndef CIRCUITCAPACITOR_H
#define CIRCUITCAPACITOR_H

#include "circuitobject.h"

class CircuitCapacitor : public CircuitObject
{
public:
  CircuitCapacitor(Coordinate begin, float scale, quint16 rotation);
  CircuitCapacitor(QDataStream& in);
  ~CircuitCapacitor();
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

#endif // CIRCUITCAPACITOR_H
