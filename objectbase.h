#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "objectabstract.h"

class ObjectBase : public ObjectAbstract {
public:
  ObjectBase(QPoint p, quint16 a, K::objectType t, quint32 id);
  ObjectBase(QDataStream &in, K::objectType t);
  ~ObjectBase();
  virtual void draw(QPainter &p);
  virtual void save(QDataStream &out);
  virtual bool move(QPoint p);
  virtual bool release();
  virtual bool rotate45();
  virtual bool rotate90();
  virtual bool rotate315();
  virtual bool rotate270();
  virtual void moveBy(QPoint d);
  virtual void moveByGS(QPoint gs);
  virtual QPoint acceptMove();
  virtual void dropMove();
  void setColor(QColor c);
  QColor getColor();
  bool isColorSet();
  virtual void doubleClick();

protected:
  virtual void drawObject(QPainter &p) = 0;
  virtual void saveSettings(QDataStream &out) = 0;
  virtual void loadSettings(QDataStream &in) = 0;
  QPoint point;
  quint16 angle;
  QPoint moved = QPoint(0, 0);
  QColor color;
  bool colorB = false;
};

#endif // OBJECTBASE_H
