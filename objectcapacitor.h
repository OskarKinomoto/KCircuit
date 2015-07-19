#ifndef OBJECTCAPACITOR_H
#define OBJECTCAPACITOR_H

#include "objectbase.h"

#include <QtGlobal>

class ObjectCapacitor : public ObjectBase {
public:
  ObjectCapacitor(QPoint p, quint16 a, quint32 id);
  ObjectCapacitor(QDataStream &in);
  ~ObjectCapacitor();
  virtual bool isPointOverObject(QPointF p);
  virtual ObjectSettingsAbstract *settings(Circuit *c);
  QString getLabel() const;
  void setLabel(const QString &value);
  enum TYPE : quint8 { NORMAL = 0, POLARIZED, DECADE };

  TYPE getTyp() const;
  void setTyp(int value);

protected:
  virtual void drawObject(QPainter &p);
  virtual void saveSettings(QDataStream &out);
  virtual void loadSettings(QDataStream &in);

private:
  QString label = QString("");
  float gsRendered = 0;
  QImage *labelImg = nullptr;
  TYPE typ = NORMAL;
};

#endif // OBJECTCAPACITOR_H
