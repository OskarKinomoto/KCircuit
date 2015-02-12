#include "historynodedeleteobject.h"
#include "circuit.h"

HistoryNodeDeleteObject::HistoryNodeDeleteObject(AbstractCircuitObject *ob)
{
  object = ob;
}

HistoryNodeDeleteObject::~HistoryNodeDeleteObject()
{
  if(removed) delete object;
}

void HistoryNodeDeleteObject::back(Circuit *c)
{
  c->addObject(object, false);
  removed = false;
}

void HistoryNodeDeleteObject::redo(Circuit *c)
{
  c->removeObject(object, false);
  removed = true;
}

