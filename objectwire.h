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

  virtual bool isPointOverObject(QPointF p);

  virtual void moveBy(QPoint d);
  virtual void moveByGS(QPoint gs);
  virtual QPoint acceptMove();
  virtual void dropMove();
  virtual void doubleClick();

  virtual bool rotate90();

  virtual ObjectSettingsAbstract * settings(Circuit * c);
private:
  std::vector<QPoint> points;
  std::vector<bool> typ;
  K::WIRE_MODE mode;
  QPoint moved = QPoint(0,0);

  static bool isPointOverWirePart(QPoint &a, QPoint &b, QPointF &c, float dist);
};

#endif // OBJECTWIRE_H
