#include "historynoderemove.h"
#include "circuit.h"

HistoryNodeRemove::HistoryNodeRemove(ObjectAbstract *o) { object = o; }

HistoryNodeRemove::~HistoryNodeRemove() {
  if (removed)
    delete object;
}

void HistoryNodeRemove::undo(Circuit *c) {
  c->addObject(object);
  removed = false;
}

void HistoryNodeRemove::redo(Circuit *c) {
  c->removeObject(object);
  removed = true;
}
