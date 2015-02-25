#ifndef OBJECTRESISTOR_H
#define OBJECTRESISTOR_H

#include "objectbase.h"

#include <QtGlobal>

class ObjectResistor : public ObjectBase
{
public:
  ObjectResistor(QPoint p, quint16 a, quint32 id);
  ObjectResistor(QDataStream &in);
  ~ObjectResistor();
  virtual bool isPointOverObject(QPointF p);
  virtual ObjectSettingsAbstract * settings(Circuit *c);
  QString getLabel() const;
  void setLabel(const QString &value);
  enum TYPE : quint8{NORMAL = 0, POTENTIOMETR, DECADE, THREMISTOR};

  TYPE getTyp() const;
  void setTyp(int value);

protected:
  virtual void drawObject(QPainter& p);
  virtual void saveSettings(QDataStream &out);
  virtual void loadSettings(QDataStream &in);
private:
  QString label = QString("");
  float gsRendered = 0;
  QImage * labelImg = nullptr;
  TYPE typ = NORMAL;

};

#endif // OBJECTRESISTOR_H
