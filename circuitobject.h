#ifndef CIRCUITOBJECT_H
#define CIRCUITOBJECT_H

#include "abstractcircuitobject.h"

class CircuitObject : public AbstractCircuitObject
{
protected:
  Coordinate cords;
public:
  CircuitObject();
  virtual ~CircuitObject();
};

#endif // CIRCUITOBJECT_H
