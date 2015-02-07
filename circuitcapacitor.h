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
  float constexpr static wspr = sqrt(2);
};

#endif // CIRCUITCAPACITOR_H
