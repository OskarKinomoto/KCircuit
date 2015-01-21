#include "circuitwidget.h"

CircuitWidget::CircuitWidget(QWidget *parent) :
  QWidget(parent)
{
  layout = new QHBoxLayout();
  this->setLayout(layout);
  ObjectMenu = new QWidget();
  scroll = new CircuitScrollArea();
  layout->addWidget(scroll);
  layout->addWidget(ObjectMenu);

  l = new QHBoxLayout();
  ObjectMenu->setLayout(l);
  l1 = new QLabel(tr("kotek"));
  l->addWidget(l1);

  render = new CircuitRenderArea(scroll);
  scroll->setWidget(render);


}
