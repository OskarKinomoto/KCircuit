#ifndef OBJECTLISTWIDGETITEM_H
#define OBJECTLISTWIDGETITEM_H

#include <QtWidgets>
#include "include.h"

class ObjectListWidgetItem : public QListWidgetItem, public K::info
{
public:
  ObjectListWidgetItem(K::info info, QListWidget * parent);
  ~ObjectListWidgetItem();
};

#endif // OBJECTLISTWIDGETITEM_H
