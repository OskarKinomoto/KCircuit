#include "historynodemove.h"

#include "circuit.h"
#include "objectabstract.h"

HistoryNodeMove::HistoryNodeMove(ObjectAbstract *o, QPoint moved) {
  object = o;
  move = moved;
}

HistoryNodeMove::~HistoryNodeMove() {}

void HistoryNodeMove::undo(Circuit *c) {
  object->moveByGS(-move);
  c->update();
}

void HistoryNodeMove::redo(Circuit *c) {
  object->moveByGS(move);
  c->update();
}
