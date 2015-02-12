#ifndef HISTORYNODENEWOBJECT_H
#define HISTORYNODENEWOBJECT_H

#include "abstractcircuitobject.h"
#include "abstracthistorynode.h"

class HistoryNodeNewObject : public AbstractHistoryNode
{
public:
  HistoryNodeNewObject(AbstractCircuitObject *ob);
  ~HistoryNodeNewObject();
  void virtual back(Circuit * c);
  void virtual redo(Circuit * c);
private:
  AbstractCircuitObject * object;
  bool removed = false;
};

#endif // HISTORYNODENEWOBJECT_H
