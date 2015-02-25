#ifndef RIGHTWIDGETVIEW_H
#define RIGHTWIDGETVIEW_H

#include <QWidget>
#include <QSplitter>

#include "listobjects.h"

#include "objectsettingsabstract.h"

class Circuit;

class RightWidgetView : public QWidget
{
  Q_OBJECT
public:
  explicit RightWidgetView(Circuit *circuit, QWidget *parent = 0);
  ~RightWidgetView();

  ListObjects * a;

  void setObjectSettings(ObjectSettingsAbstract * osa);

signals:

public slots:

protected:
  QLayout * l;
  QSplitter * s;
  Circuit * c;
  ObjectSettingsAbstract * b;
};

#endif // RIGHTWIDGETVIEW_H
