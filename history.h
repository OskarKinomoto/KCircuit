#ifndef HISTORY_H
#define HISTORY_H

#include "historynodeabstract.h"
#include "historynodenew.h"
#include "historynoderemove.h"

#include <list>

class Circuit;

class History
{
public:
  History(Circuit * circuit);
  ~History();
  void add(HistoryNodeAbstract * node);
  void undo();
  void redo();
  bool backable();
  bool forwardable();
private:
  Circuit * c;
  std::list<HistoryNodeAbstract *> history;
  std::list<HistoryNodeAbstract *>::iterator now;
};

#endif // HISTORY_H
