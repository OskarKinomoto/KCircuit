#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "circuitmodel.h"
#include "circuitview.h"

class Circuit : public CircuitView, public CircuitModel {
  Q_OBJECT
public:
  Circuit(CircuitSettings settings);
  Circuit(QString path);
  virtual ~Circuit();

  void setTool(K::tool::tool t);

  void rotate45();
  void rotate90();
  void rotate270();
  void rotate315();

  bool undo();
  bool redo();

public slots:
  void scale(bool s);
  void paint(QPaintEvent *p);
  void mouseMoved(QPoint p);
  void mouseDraged(QPoint d);
  void leave();
  void release();
  void press(QMouseEvent *e);
  void removeCurrent();
  void showContextMenu(const QPoint &pos);
  void doubleClick();

private:
  void updateSize();
  void init();

  QAction *removeCurrentA;
  QMenu contextMenu;

signals:
  void updatedSize();
};

#endif // CIRCUIT_H
