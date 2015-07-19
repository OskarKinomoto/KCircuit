#ifndef OBJECTABSTRACT_H
#define OBJECTABSTRACT_H

#include "global.h"

#include <QtGlobal>
#include <QString>
#include <QPainter>
#include "objectsettingsabstract.h"

class ObjectAbstract;

namespace K {
enum objectType : quint32 { WIRE = 0, RESISTOR = 1, COIL = 2, CAPACITOR = 3 };
struct objectInfo {
  K::objectType type;
  QString name;
  ObjectAbstract *ptr;
};
}

class ObjectAbstract {
public:
  ObjectAbstract(K::objectType t, quint32 id);
  ObjectAbstract(K::objectType t, QDataStream &in);
  virtual ~ObjectAbstract();

  virtual void draw(QPainter &p) = 0;
  virtual void save(QDataStream &out) = 0;
  virtual bool move(QPoint p) = 0;
  virtual bool release() = 0;
  virtual bool rotate45();
  virtual bool rotate90();
  virtual bool rotate315();
  virtual bool rotate270();

  virtual bool isPointOverObject(QPointF p) = 0;

  virtual void moveBy(QPoint d) = 0;
  virtual void moveByGS(QPoint gs) = 0;
  virtual QPoint acceptMove() = 0;
  virtual void dropMove() = 0;

  virtual ObjectSettingsAbstract *settings(Circuit *c) = 0;

  K::objectInfo info();

  inline QString getName() { return name; }
  inline void setName(QString n) { name = n; }

protected:
  K::objectType type;
  QString name;
  quint32 ID;

private:
  static int counter;
};

#endif // OBJECTABSTRACT_H
