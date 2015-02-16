#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "objectabstract.h"

class ObjectBase : public ObjectAbstract
{
public:
  ObjectBase(QPoint p, quint16 a, K::objectType t, quint32 id);
  ObjectBase(QDataStream &in, K::objectType t);
  ~ObjectBase();
  virtual void draw(QPainter& p);
  virtual void save(QDataStream &out);
  virtual bool move(QPoint p);
  virtual bool release();
  virtual bool rotate45();
  virtual bool rotate90();
protected:
  virtual void drawObject(QPainter& p) = 0;
  virtual void saveSettings(QDataStream &out) = 0;
  QPoint point;
  quint16 angle;
};

#endif // OBJECTBASE_H
