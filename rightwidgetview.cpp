#include "rightwidgetview.h"

#include <QGridLayout>
#include <QLabel>

#include "circuit.h"

RightWidgetView::RightWidgetView(Circuit *circuit, QWidget *parent)
    : QWidget(parent) {
  this->setMinimumWidth(150);
  this->setMaximumWidth(250);
  c = circuit;
  l = new QGridLayout(this);
  s = new QSplitter();
  s->setOrientation(Qt::Vertical);
  l->addWidget(s);
  a = new ListObjects(c);
  s->addWidget(a);

  b = new ObjectSettingsAbstract(nullptr);
  s->addWidget(b);

  s->setCollapsible(0, false);
  s->setCollapsible(1, false);
}

RightWidgetView::~RightWidgetView() {}

void RightWidgetView::setObjectSettings(ObjectSettingsAbstract *osa) {
  auto tmp = s->sizes();
  delete b;
  if (osa)
    b = osa;
  else
    b = new ObjectSettingsAbstract(nullptr);
  s->addWidget(b);
  s->setCollapsible(1, false);
  s->setSizes(tmp);
}
