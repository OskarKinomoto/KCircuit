#ifndef LISTOBJECTS_H
#define LISTOBJECTS_H

#include <QListWidget>
#include "listobjectsitem.h"

class Circuit;

#include <QMenu>

class ListObjects : public QListWidget
{
  Q_OBJECT
public:
  ListObjects(Circuit * circuit);
  ~ListObjects();
public slots:
  void load();

private:
  Circuit * c;
  QAction * remove;
  QMenu contextMenu;

  ListObjectsItem * cur = nullptr;
  ListObjectsItem * prev = nullptr;

public slots:
  void ShowContextMenu(const QPoint &pos);
  void activated ( QListWidgetItem * item );

protected:
  void mousePressEvent ( QMouseEvent * event );
  void mouseReleaseEvent ( QMouseEvent * event );
};

#endif // LISTOBJECTS_H
