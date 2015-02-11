#include "objectlistwidgetitem.h"

ObjectListWidgetItem::ObjectListWidgetItem(K::info info, QListWidget *parent) : QListWidgetItem(info.name, parent), K::info(info)
{

}

ObjectListWidgetItem::~ObjectListWidgetItem()
{

}

