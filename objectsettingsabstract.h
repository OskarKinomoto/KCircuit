#ifndef OBJECTSETTINGSABSTRACT_H
#define OBJECTSETTINGSABSTRACT_H

#include <QtWidgets>

class Circuit;

class ObjectSettingsAbstract : public QWidget
{
  Q_OBJECT
public:
  explicit ObjectSettingsAbstract(Circuit *circuit);
  virtual ~ObjectSettingsAbstract();

signals:

public slots:

protected:
  QFormLayout * l;
  Circuit * c;

};

#endif // OBJECTSETTINGSABSTRACT_H
