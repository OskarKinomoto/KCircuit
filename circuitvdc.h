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
};

#endif // CIRCUITVDC_H
