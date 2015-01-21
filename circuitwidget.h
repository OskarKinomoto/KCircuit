#ifndef CIRCUITWIDGET_H
#define CIRCUITWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "circuitscrollarea.h"
#include "circuitrenderarea.h"

class CircuitWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CircuitWidget(QWidget *parent = 0);

signals:

public slots:


private:
  QLayout * layout;
  QScrollArea * scroll;
  QPaintEngine * en;
  QWidget * ObjectMenu;
  QLabel * l1;
  QLayout * l;
  QWidget * frame;
  CircuitRenderArea * render;
};

#endif // CIRCUITWIDGET_H
