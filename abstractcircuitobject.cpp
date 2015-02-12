#include "abstractcircuitobject.h"




AbstractCircuitObject::~AbstractCircuitObject()
{
}


AbstractCircuitObject::AbstractCircuitObject(QDataStream &in)
{
  in >> num;
}
