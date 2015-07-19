#ifndef HISTORYNODEROTATE_H
#define HISTORYNODEROTATE_H

#include "historynodeabstract.h"

class ObjectAbstract;

#include <QtGlobal>

class HistoryNodeRotate : public HistoryNodeAbstract {
public:
  HistoryNodeRotate(ObjectAbstract *o, quint16 rotation);
  ~HistoryNodeRotate();
  virtual void undo(Circuit *c);
  virtual void redo(Circuit *c);

private:
  ObjectAbstract *object;
  quint16 rotation;
};

#endif // HISTORYNODEROTATE_H
