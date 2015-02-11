#include "infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) : QSplitter(parent)
{
  list = new ObjectListWidget(this);
}

InfoWidget::~InfoWidget()
{

}

void InfoWidget::update(Circuit *c)
{
  list->update(c);
}

