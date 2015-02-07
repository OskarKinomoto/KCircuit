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
  constexpr static float wspr = (2.5 + sqrt(2) + 0.5/sqrt(2));
};

#endif // CIRCUITRESISTOR_H
