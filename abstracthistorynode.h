#ifndef ABSTRACTHISTORYNODE_H
#define ABSTRACTHISTORYNODE_H

class Circuit;

class AbstractHistoryNode
{
public:
  AbstractHistoryNode();
  virtual ~AbstractHistoryNode();
  void virtual back(Circuit * c) = 0;
  void virtual redo(Circuit * c) = 0;
};

#endif // ABSTRACTHISTORYNODE_H
