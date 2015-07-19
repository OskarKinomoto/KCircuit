#ifndef HISTORYNODENEW_H
#define HISTORYNODENEW_H

#include "historynodeabstract.h"

class ObjectAbstract;

class HistoryNodeNew : public HistoryNodeAbstract {
public:
  HistoryNodeNew(ObjectAbstract *o);
  ~HistoryNodeNew();
  virtual void undo(Circuit *c);
  virtual void redo(Circuit *c);

private:
  ObjectAbstract *object;
  bool removed = false;
};

#endif // HISTORYNODENEW_H
