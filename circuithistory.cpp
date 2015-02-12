#include "circuithistory.h"

CircuitHistory::CircuitHistory(Circuit *circuit)
{
  c = circuit;
  now = history.end();
}

CircuitHistory::~CircuitHistory()
{
  for( auto itr : history)
    {
      delete itr;
    }
}

void CircuitHistory::addHistory(AbstractHistoryNode *node)
{
  history.erase(now, history.end());
  history.push_back(node);
  now = history.end();
}

void CircuitHistory::undo()
{
  if(backable())
    {
      --now;
      (*now)->back(c);
    }
}

void CircuitHistory::redo()
{
  if(forwardable())
    {
      (*now)->redo(c);
      ++now;
    }
}

bool CircuitHistory::backable()
{
  return now != history.begin();
}

bool CircuitHistory::forwardable()
{
  return now != history.end();
}

