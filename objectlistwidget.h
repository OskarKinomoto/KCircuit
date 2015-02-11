#ifndef OBJECTLISTWIDGET_H
#define OBJECTLISTWIDGET_H

#include <QtWidgets>
#include "circuit.h"
#include <vector>

class ObjectListWidget : public QListWidget
{
public:
  ObjectListWidget(QWidget * parent);
  ~ObjectListWidget();
  void update(Circuit * c);
private:
  std::vector<K::info> lista;
};

#endif // OBJECTLISTWIDGET_H
