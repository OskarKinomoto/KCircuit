#ifndef HISTORYNODEABSTRACT_H
#define HISTORYNODEABSTRACT_H

class Circuit;

class HistoryNodeAbstract
{
public:
  HistoryNodeAbstract();
  virtual ~HistoryNodeAbstract();
  virtual void undo(Circuit * c) = 0;
  virtual void redo(Circuit * c) = 0;
};

#endif // HISTORYNODEABSTRACT_H
