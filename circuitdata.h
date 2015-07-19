#ifndef CIRCUITDATA_H
#define CIRCUITDATA_H

#include <QRect>
#include "tools.h"

class CircuitData {
public:
  CircuitData();
  virtual ~CircuitData();
  void setIndex(int i);

protected:
  QRect visibleRectangle;
  K::tool::tool tool;
  int index;
};

#endif // CIRCUITDATA_H
