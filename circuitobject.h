#ifndef CIRCUITOBJECT_H
#define CIRCUITOBJECT_H

#include "abstractcircuitobject.h"

class CircuitObject : public AbstractCircuitObject
{
private:
  Coordinate coords;
public:
  CircuitObject(Coordinate c);
  CircuitObject(int x = 0, int y = 0);
  virtual ~CircuitObject();
};

#endif // CIRCUITOBJECT_H
