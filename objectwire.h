#ifndef OBJECTWIRE_H
#define OBJECTWIRE_H

#include "objectabstract.h"

class ObjectWire : public ObjectAbstract
{
public:
  ObjectWire(QPoint p, quint32 id);
  ObjectWire(QDataStream &in);
  ~ObjectWire();

  virtual void draw(QPainter& p);
  virtual void save(QDataStream &out);
  virtual bool move(QPoint p);
  virtual bool release();

  virtual bool isPointOverObject(QPointF p) = 0;

  virtual void moveBy(QPoint d);
  virtual void moveByGS(QPoint gs);
  virtual QPoint acceptMove();
  virtual void dropMove();
  virtual void doubleClick();

  virtual ObjectSettingsAbstract * settings(Circuit * c);
private:
  std::vector<QPoint> points;
  K::WIRE_MODE mode;
};

#endif // OBJECTWIRE_H
