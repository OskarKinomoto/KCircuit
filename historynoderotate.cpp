#include "historynoderotate.h"

#include "circuit.h"
#include "objectabstract.h"

HistoryNodeRotate::HistoryNodeRotate(ObjectAbstract *o, quint16 rotation) {
  object = o;
  HistoryNodeRotate::rotation = rotation;
}

HistoryNodeRotate::~HistoryNodeRotate() {}

void HistoryNodeRotate::undo(Circuit *c) {
  switch (rotation) {
  case 45:
    object->rotate315();
    break;
  case 90:
    object->rotate270();
    break;
  case 270:
    object->rotate90();
    break;
  case 315:
    object->rotate45();
    break;
  }
  c->update();
}

void HistoryNodeRotate::redo(Circuit *c) {
  switch (rotation) {
  case 45:
    object->rotate45();
    break;
  case 90:
    object->rotate90();
    break;
  case 270:
    object->rotate270();
    break;
  case 315:
    object->rotate315();
    break;
  }
  c->update();
}
