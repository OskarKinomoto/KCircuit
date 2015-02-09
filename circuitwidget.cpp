#include "circuitwidget.h"
#include "mainwindow.h"
#define selectedTool MainWindow::selectedTool

//extern void CircuitScrollArea::setTitle(QString &s);

CircuitWidget::CircuitWidget(Circuit *_circuit, CircuitScrollArea *parent) : QWidget(parent)
{
  circuit = _circuit;
  scroll = parent;
  this->updateSize();
  this->setAutoFillBackground(true);
  this->setBackgroundRole(QPalette::Base);
  this->setFocusPolicy(Qt::StrongFocus);
}

CircuitWidget::~CircuitWidget()
{
  delete circuit;
}

void CircuitWidget::centering()
{
  auto hm = scroll->horizontalScrollBar()->maximum();
  auto vm = scroll->verticalScrollBar()->maximum();
  scroll->horizontalScrollBar()->setSliderPosition(hm/2);
  scroll->verticalScrollBar()->setSliderPosition(vm/2);
}

void CircuitWidget::updateTitle()
{
  ((CircuitScrollArea*)this->parentWidget())->setTitle(circuit->name());
}

void CircuitWidget::updateSize()
{
  float v = float(scroll->verticalScrollBar()->value())/scroll->verticalScrollBar()->maximum();
  float h = float(scroll->horizontalScrollBar()->value())/scroll->horizontalScrollBar()->maximum();
  if(!scroll->horizontalScrollBar()->maximum()) h = 0.5;
  if(!scroll->verticalScrollBar()->maximum()) v = 0.5;

  this->resize(circuit->width() * circuit->scale(), circuit->height() * circuit->scale());

  scroll->verticalScrollBar()->setSliderPosition(scroll->verticalScrollBar()->maximum()*v);
  scroll->horizontalScrollBar()->setSliderPosition(scroll->horizontalScrollBar()->maximum()*h);

  this->forceMouseMoveEvent();
}

bool CircuitWidget::inVisibleRect(int x, int y)
{
  return(x > visibleRect.x() && y > visibleRect.y() && y < visibleRect.y() + visibleRect.height() && x < visibleRect.x() + visibleRect.width());
}

void CircuitWidget::grabMouse()
{
  grabedMouse = true;
  QWidget::grabMouse();
}

void CircuitWidget::releaseMouse()
{
  grabedMouse = false;
  QWidget::releaseMouse();
}

void CircuitWidget::forceMouseMoveEvent()
{
  QMouseEvent * event = new QMouseEvent(QEvent::MouseMove, this->mapFromGlobal(QCursor::pos()), Qt::NoButton, Qt::NoButton, 0);
  circuit->mouseEvent(event);
}

void CircuitWidget::updateName()
{
  scroll->setTitle(circuit->name());
}

void CircuitWidget::paintEvent(QPaintEvent *p)
{
  visibleRect = p->rect();
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::HighQualityAntialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);

  circuit->draw(painter);
}

void CircuitWidget::mouseMoveEvent(QMouseEvent *event)
{
  event = new QMouseEvent(event->type(), event->pos(), Qt::NoButton, Qt::NoButton, 0);

  circuit->mouseEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if(ignoreMouse)
    {
      ignoreMouse = false;
      return;
    }
  int x = event->x();
  int y = event->y();

  if(!inVisibleRect(x,y))
    {
      event->ignore();
      return;
    }
  circuit->mouseEvent(event);
}

void CircuitWidget::mousePressEvent(QMouseEvent *event)
{
  event->ignore();
}

void CircuitWidget::mouseDoubleClickEvent(QMouseEvent *)
{
  ignoreMouse = true;
  circuit->doubleClick();
}

#undef selectedTool
