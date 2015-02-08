#ifndef CIRCUITADC_H
#define CIRCUITADC_H

#include "circuitobject.h"

class CircuitADC : public CircuitObject
{
public:
  CircuitADC(Coordinate begin, float scale, quint16 rotation);
  CircuitADC(QDataStream& in);
  ~CircuitADC();
  virtual void draw(QPainter&p, float scale);
  virtual bool save(QDataStream& out);
};
#endif // CIRCUITADC_H
