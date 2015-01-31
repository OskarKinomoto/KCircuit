#include "circuitobject.h"

CircuitObject::CircuitObject(Coordinate c)
{
  coords = c;
}

CircuitObject::CircuitObject(int x, int y)
{
  coords = Coordinate(x,y);
}

CircuitObject::~CircuitObject()
{

}

