#include "objectlistwidget.h"

ObjectListWidget::ObjectListWidget(QWidget *parent) : QListWidget(parent)
{
  this->setMinimumWidth(100);
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
          this, SLOT(ShowContextMenu(const QPoint&)));
  connect(this, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(activated(QListWidgetItem*)));

  remove = new QAction(QIcon::fromTheme("window-close"), "Remove", nullptr);
  contextMenu.addActions({remove});
}

ObjectListWidget::~ObjectListWidget()
{

}

void ObjectListWidget::update(Circuit *c)
{
  auto * l = c->lista();
  this->clear();
  circuit = c;

  for(auto itr = l->begin(); itr != l->end(); itr++)
    {
      if(!(*itr)->isDrawing())
        {
          K::info info = (*itr)->info();
          new ObjectListWidgetItem(info, this);
        }
    }
}

void ObjectListWidget::add(K::info &info)
{
  new ObjectListWidgetItem(info, this);
}

void ObjectListWidget::ShowContextMenu(const QPoint& pos) // this is a slot
{
  if(!current) return;
  // for most widgets
  QPoint globalPos = this->mapToGlobal(pos);
  // for QAbstractScrollArea and derived classes you would use:
  /// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

  QAction* selectedItem = contextMenu.exec(globalPos);
  if(selectedItem)
    {
      if(selectedItem == remove)
        {
          circuit->removeObject(current->ptr);
          delete current;
          prev = nullptr;
          current = nullptr;
        }
    }
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




