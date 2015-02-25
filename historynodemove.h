#ifndef HISTORYNODEMOVE_H
#define HISTORYNODEMOVE_H

#include "historynodeabstract.h"

class ObjectAbstract;

#include <QtGlobal>
#include <QPoint>

class HistoryNodeMove : public HistoryNodeAbstract
{
public:
  HistoryNodeMove(ObjectAbstract * o, QPoint moved);
  ~HistoryNodeMove();
  virtual void undo(Circuit * c);
  virtual void redo(Circuit * c);
private:
  ObjectAbstract * object;
  QPoint move;
};

#endif // HISTORYNODEMOVE_H
