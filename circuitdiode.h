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
  constexpr static float sqrt2 = sqrt(2);
};


#endif // CIRCUITDIODE_H
