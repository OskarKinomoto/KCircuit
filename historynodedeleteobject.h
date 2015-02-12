#ifndef HISTORYNODEDELETEOBJECT_H
#define HISTORYNODEDELETEOBJECT_H


#include "abstractcircuitobject.h"
#include "abstracthistorynode.h"

class HistoryNodeDeleteObject : public AbstractHistoryNode
{
public:
  HistoryNodeDeleteObject(AbstractCircuitObject *ob);
  ~HistoryNodeDeleteObject();
  void virtual back(Circuit * c);
  void virtual redo(Circuit * c);
private:
  AbstractCircuitObject * object;
  bool removed = true;
};

#endif // HISTORYNODEDELETEOBJECT_H
