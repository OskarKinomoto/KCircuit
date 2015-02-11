#include "abstractcircuitobject.h"




AbstractCircuitObject::~AbstractCircuitObject()
{
  qDebug() << "dekontruktor";
}


AbstractCircuitObject::AbstractCircuitObject(QDataStream &in)
{
  in >> num;
}
