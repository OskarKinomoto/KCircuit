#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QtWidgets>
#include "circuit.h"
#include "objectlistwidget.h"

class InfoWidget : public QSplitter
{
  Q_OBJECT
public:
  explicit InfoWidget(QWidget *parent);
  ~InfoWidget();

  void update(Circuit * c);
  Circuit * current;
private:
  ObjectListWidget * list;
signals:

public slots:
};

#endif // INFOWIDGET_H
