#ifndef OBJECTLISTWIDGET_H
#define OBJECTLISTWIDGET_H

#include <QtWidgets>
#include "circuit.h"
#include "objectlistwidgetitem.h"
#include <vector>

class ObjectListWidget : public QListWidget
{
  Q_OBJECT
public:
  ObjectListWidget(QWidget * parent);
  ~ObjectListWidget();
  void update(Circuit * c);
  void add(K::info& info);
public slots:
  void ShowContextMenu(const QPoint &pos);
  void activated ( QListWidgetItem * item );
private:
  ObjectListWidgetItem * current = nullptr;
  ObjectListWidgetItem * prev = nullptr;
  Circuit * circuit = nullptr;

  QAction * remove;
  QMenu contextMenu;
protected:
  void mousePressEvent ( QMouseEvent * event );
  void mouseReleaseEvent ( QMouseEvent * event );
};

#endif // OBJECTLISTWIDGET_H
