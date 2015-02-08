#ifndef CIRCUITGENERATOR_H
#define CIRCUITGENERATOR_H


#include "circuitobject.h"

class CircuitGenerator : public CircuitObject
{
public:
  CircuitGenerator(Coordinate begin, float scale, quint16 rotation);
  CircuitGenerator(QDataStream& in);
  ~CircuitGenerator();
  virtual void draw(QPainter&p, float scale);
  virtual bool save(QDataStream& out);
};

#endif // CIRCUITGENERATOR_H
