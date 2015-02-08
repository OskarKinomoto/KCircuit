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
};

#endif // CIRCUITCOIL_H
