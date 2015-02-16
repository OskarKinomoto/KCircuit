#ifndef RIGHTWIDGETVIEW_H
#define RIGHTWIDGETVIEW_H

#include <QWidget>
#include <QSplitter>

#include "listobjects.h"

class Circuit;

class RightWidgetView : public QWidget
{
  Q_OBJECT
public:
  explicit RightWidgetView(Circuit *circuit, QWidget *parent = 0);
  ~RightWidgetView();

  ListObjects * a;

signals:

public slots:

protected:
  QLayout * l;
  QSplitter * s;
  Circuit * c;
};

#endif // RIGHTWIDGETVIEW_H
