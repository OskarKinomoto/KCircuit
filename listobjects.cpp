#include "listobjects.h"
#include "circuit.h"

//#include <QAction>

ListObjects::ListObjects(Circuit *circuit) {
  c = circuit;
  c->setList(this);
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  this->setMaximumHeight(250);

  remove = new QAction(QIcon::fromTheme("window-close"), "Remove", nullptr);
  contextMenu.addActions({remove});

  connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this,
          SLOT(ShowContextMenu(const QPoint &)));
  connect(this, SIGNAL(itemPressed(QListWidgetItem *)), this,
          SLOT(activated(QListWidgetItem *)));

  this->load();
}

ListObjects::~ListObjects() {}

void ListObjects::setCurrent(ObjectAbstract *o) {
  if (o)
    this->setCurrentItem(this->findItems(o->getName(), Qt::MatchExactly)[0]);
  else
    this->clearSelection();
}

void ListObjects::load() {
  auto &list = c->list();
  this->clear();

  for (auto itr = list.begin(); itr != list.end(); ++itr)
    if (!c->isDrawing(*itr))
      new ListObjectsItem((*itr)->info(), this);
}

void ListObjects::ShowContextMenu(const QPoint &pos) {
  if (!cur)
    return;
  QPoint globalPos = this->mapToGlobal(pos);
  // for QAbstractScrollArea and derived classes you would use:
  /// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

  QAction *selectedItem = contextMenu.exec(globalPos);
  if (selectedItem) {
    if (selectedItem == remove) {
      c->removeObject(cur->ptr, true);
      c->update();
      prev = nullptr;
      cur = nullptr;
    }
  }
}

void ListObjects::activated(QListWidgetItem *item) {
  cur = static_cast<ListObjectsItem *>(item);
  c->setCurrent(cur->ptr);
  c->update();
}

void ListObjects::mousePressEvent(QMouseEvent *event) {
  prev = cur;
  cur = nullptr;
  this->clearSelection();
  c->setCurrent(nullptr);
  c->update();
  QListWidget::mousePressEvent(event);
}
