#include "history.h"

History::History(Circuit *circuit)
{
  c = circuit;
  now = history.end();
}

History::~History()
{
  for( auto itr : history)
    {
      delete itr;
    }
}

void History::add(HistoryNodeAbstract *node)
{
  for(auto itr = now; itr != history.end(); ++itr)
    delete *itr;
  history.erase(now, history.end());
  history.push_back(node);
  now = history.end();
}

void History::undo()
{
  if(backable())
    {
      --now;
      (*now)->undo(c);
    }
}

void History::redo()
{
  if(forwardable())
    {
      (*now)->redo(c);
      ++now;
    }
}

bool History::backable()
{
  return now != history.begin();
}

bool History::forwardable()
{
  return now != history.end();
}

