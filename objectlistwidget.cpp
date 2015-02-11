#include "objectlistwidget.h"

ObjectListWidget::ObjectListWidget(QWidget *parent) : QListWidget(parent)
{
  this->setMinimumWidth(100);
}

ObjectListWidget::~ObjectListWidget()
{

}

void ObjectListWidget::update(Circuit *c)
{
  lista.clear();
  auto * l = c->lista();
  lista.reserve(l->size());

  for(auto itr = l->begin(); itr != l->end(); itr++)
    {
      K::info info = (*itr)->info();
      //lista.push_back(info);
      new QListWidgetItem(info.name, this);
    }
}

