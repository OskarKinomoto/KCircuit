#include "rightwidgetview.h"

#include <QGridLayout>
#include <QLabel>

#include "circuit.h"

RightWidgetView::RightWidgetView(Circuit * circuit, QWidget *parent) : QWidget(parent)
{
  this->setMinimumWidth(100);
  this->setMaximumWidth(200);
  c = circuit;
  l = new QGridLayout(this);
  s = new QSplitter();
  l->addWidget(s);
  a = new ListObjects(c);
  s->addWidget(a);
}

RightWidgetView::~RightWidgetView()
{

}

