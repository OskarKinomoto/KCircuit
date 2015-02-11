#ifndef CIRCUITWIRE_H
#define CIRCUITWIRE_H

#include <vector>

#include <QDebug>

#include "abstractcircuitobject.h"



class CircuitWire : public AbstractCircuitObject
{
private:
  std::vector<Coordinate> cords;
  bool drawing = false;

public:
  CircuitWire(Coordinate begin, float scale, quint32 num);
  CircuitWire(QDataStream& in);
  ~CircuitWire();
  virtual bool isSmallRotate() { return false; }
  virtual void draw(QPainter&p, float scale);
  virtual K::status mouseEvent(QMouseEvent * event, float scale);
  virtual bool save(QDataStream& out);
  virtual K::status doubleClick();
  virtual K::info info();
};

#endif // CIRCUITWIRE_H
