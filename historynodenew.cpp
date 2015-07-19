#include "historynodenew.h"

#include "circuit.h"

HistoryNodeNew::HistoryNodeNew(ObjectAbstract *o) { object = o; }

HistoryNodeNew::~HistoryNodeNew() {
  if (removed)
    delete object;
}

void HistoryNodeNew::undo(Circuit *c) {
  c->removeObject(object);
  removed = true;
}

void HistoryNodeNew::redo(Circuit *c) {
  c->addObject(object);
  removed = false;
}
