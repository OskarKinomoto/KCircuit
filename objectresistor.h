#ifndef OBJECTRESISTOR_H
#define OBJECTRESISTOR_H

#include "objectbase.h"

class ObjectResistor : public ObjectBase
{
public:
  ObjectResistor(QPoint p, quint16 a, quint32 id);
  ObjectResistor(QDataStream &in);
  ~ObjectResistor();
  virtual bool isPointOverObject(QPointF p);
protected:
  virtual void drawObject(QPainter& p);
  virtual void saveSettings(QDataStream &out);
  virtual void loadSettings(QDataStream &in);
};

#endif // OBJECTRESISTOR_H
