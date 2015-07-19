#ifndef OBJECTCOIL_H
#define OBJECTCOIL_H

#include "objectbase.h"

#include <QtGlobal>

class ObjectCoil : public ObjectBase {
public:
  ObjectCoil(QPoint p, quint16 a, quint32 id);
  ObjectCoil(QDataStream &in);
  ~ObjectCoil();
  virtual bool isPointOverObject(QPointF p);
  virtual ObjectSettingsAbstract *settings(Circuit *c);
  QString getLabel() const;
  void setLabel(const QString &value);
  enum TYPE : quint8 { NORMAL = 0 };

  TYPE getTyp() const;
  void setTyp(int value);

protected:
  virtual void drawObject(QPainter &p);
  virtual void saveSettings(QDataStream &out);
  virtual void loadSettings(QDataStream &in);
};

#endif // OBJECTCOIL_H
