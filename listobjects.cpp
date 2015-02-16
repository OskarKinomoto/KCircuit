#include "listobjects.h"
#include "circuit.h"


//#include <QAction>

ListObjects::ListObjects(Circuit *circuit)
{
  c = circuit;
  c->setList(this);
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  remove = new QAction(QIcon::fromTheme("window-close"), "Remove", nullptr);
  contextMenu.addActions({remove});

  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
  connect(this, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(activated(QListWidgetItem*)));

  this->load();

}

ListObjects::~ListObjects()
{

}

void ListObjects::load()
{
  auto& list = c->list();
  this->clear();

  for(auto itr = list.begin(); itr != list.end(); ++itr)
    if(!c->isDrawing(*itr))
      new ListObjectsItem((*itr)->info(), this);

}

void ListObjects::ShowContextMenu(const QPoint &pos)
{
  if(!cur) return;
  QPoint globalPos = this->mapToGlobal(pos);
  // for QAbstractScrollArea and derived classes you would use:
  /// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

  QAction* selectedItem = contextMenu.exec(globalPos);
  if(selectedItem)
    {
      if(selectedItem == remove)
        {
          c->removeObject(cur->ptr, true);
          c->update();
          prev = nullptr;
          cur = nullptr;
        }
    }
}

void ListObjects::activated(QListWidgetItem *item)
{
  cur = static_cast<ListObjectsItem*>(item);
}

void ListObjects::mousePressEvent(QMouseEvent *event)
{
  prev = cur;
  cur = nullptr;
  //this->clearSelection();
  QListWidget::mousePressEvent(event);
}

void ListObjects::mouseReleaseEvent(QMouseEvent *event)
{
  if(!cur)
    if(prev)
      {
        cur = prev;
        this->setCurrentItem(prev);
      }
  QListWidget::mouseReleaseEvent(event);
}

