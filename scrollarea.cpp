#include "scrollarea.h"

#include <QWheelEvent>
#include <QScrollBar>

#ifdef __linux__
#include "global.h"
#endif

ScrollArea::ScrollArea() : QScrollArea() {
  this->setBackgroundRole(QPalette::Dark);
  this->setAlignment(Qt::AlignCenter);

#ifdef __linux__
  if (K::breeze) {
    corner = new QWidget();
    corner->setAutoFillBackground(true);
    corner->setBackgroundRole(QPalette::Base);
    this->verticalScrollBar()->setAutoFillBackground(true);
    this->horizontalScrollBar()->setAutoFillBackground(true);
    this->recolorScrollBars();
  }
#endif
}

ScrollArea::~ScrollArea() {}

void ScrollArea::scrollMiddle(int dx, int dy) {
  this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - dy);
  this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() -
                                        dx);
}

void ScrollArea::centering() {
  this->horizontalScrollBar()->setValue(horizontalScrollBar()->maximum() / 2);
  this->verticalScrollBar()->setValue(verticalScrollBar()->maximum() / 2);
  this->savePos();
}

void ScrollArea::updatePosition() {
  int dh = this->horizontalScrollBar()->maximum() +
           this->horizontalScrollBar()->pageStep();
  int dv = this->verticalScrollBar()->maximum() +
           this->verticalScrollBar()->pageStep();

  if (ch)
    this->horizontalScrollBar()->setValue(horizontalScrollBar()->maximum() / 2);
  else
    this->horizontalScrollBar()->setValue(ph * dh - eh);

  if (cv)
    this->verticalScrollBar()->setValue(verticalScrollBar()->maximum() / 2);
  else
    this->verticalScrollBar()->setValue(pv * dv - ev);
}

void ScrollArea::zoom(bool b) {
  savePos();
  emit scale(b);
}

void ScrollArea::resizeEvent(QResizeEvent *event) {
  this->recolorScrollBars();
  this->updatePosition();
  QScrollArea::resizeEvent(event);
}

void ScrollArea::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() == Qt::CTRL) {
    delta += event->delta();
    if (delta >= 120) {
      delta = 0;
      savePos(event);
      emit scale(true);
    } else if (delta <= -120) {
      delta = 0;
      savePos(event);
      emit scale(false);
    }
  } else {
    emit move();
    QScrollArea::wheelEvent(event);
  }
}

#ifdef __linux__
void ScrollArea::recolorScrollBars() {
  if (K::breeze) {
    bool wh = this->verticalScrollBar()->maximum() != 0 &&
              this->horizontalScrollBar()->maximum() != 0;
    this->verticalScrollBar()->setBackgroundRole(wh ? QPalette::Base
                                                    : QPalette::Dark);
    this->horizontalScrollBar()->setBackgroundRole(wh ? QPalette::Base
                                                      : QPalette::Dark);
    this->setCornerWidget(wh ? corner : nullptr);
  }
}
#endif

void ScrollArea::savePos(QWheelEvent *e) {

  int dh = this->horizontalScrollBar()->maximum() +
           this->horizontalScrollBar()->pageStep();
  int dv = this->verticalScrollBar()->maximum() +
           this->verticalScrollBar()->pageStep();

  cv = this->verticalScrollBar()->maximum() == 0;
  ch = this->horizontalScrollBar()->maximum() == 0;
  if (e) {
    ev = e->pos().y();
    eh = e->pos().x();
  } else {
    ev = this->verticalScrollBar()->pageStep() / 2.0;
    eh = this->horizontalScrollBar()->pageStep() / 2.0;
  }
  if (!cv)
    pv = ((float)this->verticalScrollBar()->value() + ev) / dv;
  if (!ch)
    ph = ((float)this->horizontalScrollBar()->value() + eh) / dh;
}
