#include "listobjectsitem.h"

ListObjectsItem::ListObjectsItem(K::objectInfo info, QListWidget *parent)
    : QListWidgetItem(info.name, parent), K::objectInfo(info) {}

ListObjectsItem::~ListObjectsItem() {}
