#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent) : QWidget(parent) {
  this->setAutoFillBackground(true);
  this->setBackgroundRole(QPalette::Base);
  this->setFocusPolicy(Qt::StrongFocus);
}

CircuitView::~CircuitView() {}

void CircuitView::setSize(QSize size) { this->resize(size); }

void CircuitView::paintEvent(QPaintEvent *p) {
  emit paint(p);
  if (startAtCenter) {
    startAtCenter = false;
    emit centering();
  }
}

void CircuitView::enterEvent(QEvent *) {
  if (tool != K::tool::POINTER)
    this->setMouseTracking(true);
}

void CircuitView::leaveEvent(QEvent *) {
  setMouseTracking(false);
  emit leave();
}

void CircuitView::mouseMoveEvent(QMouseEvent *event) {
  if (middleButton) {
    posNow = event->pos();
    emitMoveMiddle();
  }
  emit mouseMove(event->pos());

  if (event->buttons() == Qt::LeftButton) {
    emit mouseDrag(event->pos() - curPos);
    curPos = event->pos();
  }
}

void CircuitView::mouseReleaseEvent(QMouseEvent *event) {
  if (ignoreRelease)
    ignoreRelease = false;
  else if (event->button() == Qt::LeftButton)
    emit release();
  else if (middleButton && event->button() == Qt::MiddleButton) {
    middleButton = false;
    posNow = event->pos();
    emitMoveMiddle();
  }
}

void CircuitView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::MiddleButton) {
    posStart = event->pos(), middleButton = true;
  } else {
    emit press(event);
    curPos = event->pos();
  }
  event->ignore();
}

void CircuitView::mouseDoubleClickEvent(QMouseEvent *) {
  ignoreRelease = true;
  emit doubleClick();
}

void CircuitView::emitMoveMiddle() {
  int dx = posNow.x() - posStart.x();
  int dy = posNow.y() - posStart.y();
  emit moveMiddle(dx, dy);
}
