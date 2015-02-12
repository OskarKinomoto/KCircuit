#ifndef CIRCUITHISTORY_H
#define CIRCUITHISTORY_H

#include "abstracthistorynode.h"
#include <list>

class Circuit;

class CircuitHistory
{
public:
  CircuitHistory(Circuit * circuit);
  ~CircuitHistory();
  void addHistory(AbstractHistoryNode * node);
  void undo();
  void redo();
  bool backable();
  bool forwardable();
private:
  Circuit * c;
  std::list<AbstractHistoryNode *> history;
  std::list<AbstractHistoryNode *>::iterator now;
};

#endif // CIRCUITHISTORY_H
