#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>

class ScrollArea : public QScrollArea {
  Q_OBJECT
public:
  ScrollArea();
  ~ScrollArea();

public slots:
  void scrollMiddle(int dx, int dy);
  void centering();
  void updatePosition();
  void zoom(bool b); /// TRUE zoomIn, FALSE zoomOut

signals:
  void scale(bool); /// TRUE zoomIn, FALSE zoomOut
  void move();

protected:
  virtual void resizeEvent(QResizeEvent *event);
  virtual void wheelEvent(QWheelEvent *event);

private:
#ifdef __linux__
  QWidget *corner = nullptr;
  void recolorScrollBars();
#endif
  int delta = 0;

  void savePos(QWheelEvent *e = nullptr);
  QPoint m;
  float pv;
  float ph;
  bool cv;
  bool ch;
  int ev;
  int eh;
};

#endif // SCROLLAREA_H
