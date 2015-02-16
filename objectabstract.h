#ifndef OBJECTABSTRACT_H
#define OBJECTABSTRACT_H

#include "global.h"

#include <QtGlobal>
#include <QString>
#include <QPainter>

class ObjectAbstract;

namespace K
{
  enum objectType : quint32 {RESISTOR = 1};
  struct objectInfo
  {
    K::objectType type;
    QString name;
    ObjectAbstract *  ptr;
  };
}

class ObjectAbstract
{
public:
  ObjectAbstract(K::objectType t, quint32 id);
  ObjectAbstract(K::objectType t, QDataStream &in);
  virtual ~ObjectAbstract();

  virtual void draw(QPainter& p) = 0;
  virtual void save(QDataStream &out) = 0;
  virtual bool move(QPoint p) = 0;
  virtual bool release() = 0;
  virtual bool rotate45();
  virtual bool rotate90();

  virtual bool isPointOverObject(QPointF p) = 0;

  K::objectInfo info();
protected:
  K::objectType type;
  QString name;
  quint32 ID;

private:
  static int counter;
};

#endif // OBJECTABSTRACT_H
