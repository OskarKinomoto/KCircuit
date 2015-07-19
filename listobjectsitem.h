#ifndef LISTOBJECTSITEM_H
#define LISTOBJECTSITEM_H

#include <QListWidgetItem>
#include <objectabstract.h>

class ListObjectsItem : public QListWidgetItem, public K::objectInfo {
public:
  ListObjectsItem(K::objectInfo info, QListWidget *parent);
  ~ListObjectsItem();
};

#endif // LISTOBJECTSITEM_H
