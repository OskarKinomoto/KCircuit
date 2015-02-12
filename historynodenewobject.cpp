#include "historynodenewobject.h"
#include "circuit.h"

HistoryNodeNewObject::HistoryNodeNewObject(AbstractCircuitObject * ob)
{
  object = ob;
}

HistoryNodeNewObject::~HistoryNodeNewObject()
{
  if(removed) delete object;
}

void HistoryNodeNewObject::back(Circuit *c)
{
  c->removeObject(object, false);
  removed = true;
}

void HistoryNodeNewObject::redo(Circuit *c)
{
  c->addObject(object, false);
  removed = false;
}

