#ifndef CIRCUITRESISTOR_H
#define CIRCUITRESISTOR_H

#include "circuitobject.h"

class CircuitResistor : public CircuitObject
{

public:
  CircuitResistor(Coordinate begin, float scale, quint16 rotation);
  CircuitResistor(QDataStream& in);
  ~CircuitResistor();

  virtual void draw(QPainter&p, float scale);
  virtual bool save(QDataStream& out);

private:
#ifdef MATH_CONSTEXPR
  float constexpr static wspr = 2*sqrt(2);
#elif defined(CONSTEXPR)
  float constexpr static wspr = 2*sqrt2;
#else
  float static wspr;
#endif
};

#endif // CIRCUITRESISTOR_H
