#ifndef HISTORYNODEREMOVE_H
#define HISTORYNODEREMOVE_H

#include "historynodeabstract.h"

class ObjectAbstract;

class HistoryNodeRemove : public HistoryNodeAbstract
{
public:
  HistoryNodeRemove(ObjectAbstract * o);
  ~HistoryNodeRemove();
  virtual void undo(Circuit * c);
  virtual void redo(Circuit * c);
private:
  ObjectAbstract * object;
  bool removed = true;
};

#endif // HISTORYNODEREMOVE_H
