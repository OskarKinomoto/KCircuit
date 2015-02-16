#ifndef CIRCUITVIEW_H
#define CIRCUITVIEW_H

#include <QtWidgets>

#include "circuitdata.h"

class CircuitView : public QWidget, public virtual CircuitData
{
  Q_OBJECT
public:
  explicit CircuitView(QWidget *parent = 0);
  virtual ~CircuitView();

  void setSize(QSize size);

protected:
  void paintEvent(QPaintEvent *p);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent * event);

signals:
  void paint(QPaintEvent * p);
  void mouseMove(QPoint p);
  void leave();
  void release();
  void doubleClick();
  void moveMiddle(int dx, int dy);
  void centering();
  void press(QMouseEvent * e);

public slots:

private:
  bool ignoreRelease = false;
  QPoint posStart;
  QPoint posNow;
  bool middleButton = false;
  bool startAtCenter = true;
  void emitMoveMiddle();
};

#endif // CIRCUITVIEW_H
