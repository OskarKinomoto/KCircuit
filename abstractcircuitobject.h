#ifndef ABSTRACTCIRCUITOBJECT_H
#define ABSTRACTCIRCUITOBJECT_H

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDataStream>

#include <QDebug>

#include "coordinate.h"
#include "enum.h"

#define OBJECT_VERSION 0

const int grid = 20;

class AbstractCircuitObject
{
private:
public:
  virtual ~AbstractCircuitObject() = 0;
  virtual void draw(QPainter&, float scale) = 0;
  virtual void rotate(){}
  virtual void smallRotate(){}
  virtual K::status mouseEvent(QMouseEvent * event, float scale) = 0;
  virtual bool save(QDataStream& out) = 0;
  enum status{DRAWING, END_DRAWING, DESTROY};
  virtual K::status doubleClick() = 0;
};

#endif // ABSTRACTCIRCUITOBJECT_H
