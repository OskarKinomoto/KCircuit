#include "objectlistwidget.h"

ObjectListWidget::ObjectListWidget(QWidget *parent) : QListWidget(parent)
{
  this->setMinimumWidth(100);
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
          this, SLOT(ShowContextMenu(const QPoint&)));
  connect(this, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(activated(QListWidgetItem*)));
}

ObjectListWidget::~ObjectListWidget()
{

}

void ObjectListWidget::update(Circuit *c)
{
  auto * l = c->lista();
  this->clear();

  for(auto itr = l->begin(); itr != l->end(); itr++)
    {
      K::info info = (*itr)->info();
      //lista.push_back(info);
      new ObjectListWidgetItem(info, this);
    }
}

void ObjectListWidget::ShowContextMenu(const QPoint& pos) // this is a slot
{
  if(!current) return;
  // for most widgets
  QPoint globalPos = this->mapToGlobal(pos);
  // for QAbstractScrollArea and derived classes you would use:
  /// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);
  QMenu myMenu;
  myMenu.addAction("Menu Item 1");
  // ...
  qDebug() << current->name;
  QAction* selectedItem = myMenu.exec(globalPos);
  if (selectedItem)
    {
      // something was chosen, do stuff
    }
  else
    {
      // nothing was chosen
    }
  QWidget::update();
}

void ObjectListWidget::activated(QListWidgetItem *item)
{
  current = (ObjectListWidgetItem*) item;
}

void ObjectListWidget::mousePressEvent(QMouseEvent *event)
{
  prev = current;
  current = nullptr;
  //this->clearSelection();
  QListWidget::mousePressEvent(event);
}

void ObjectListWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if(!current)
    {
      if(prev)
        {
          current = prev;
          this->setCurrentItem(prev);
        }
    }

  QListWidget::mouseReleaseEvent(event);
}




