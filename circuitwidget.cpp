#include "circuitwidget.h"
#include "mainwindow.h"
#define selectedTool MainWindow::selectedTool

//extern void CircuitScrollArea::setTitle(QString &s);

CircuitWidget::CircuitWidget(Circuit *_circuit, QWidget *parent) : QWidget(parent)
{
  circuit = _circuit;
  this->updateSize();
  this->setAutoFillBackground(true);
  this->setBackgroundRole(QPalette::Base);
  this->setFocusPolicy(Qt::StrongFocus);
}

CircuitWidget::~CircuitWidget()
{

}

void CircuitWidget::updateTitle()
{
  ((CircuitScrollArea*)this->parentWidget())->setTitle(circuit->name());
}

void CircuitWidget::updateSize()
{
  this->resize(circuit->width() * circuit->scale(), circuit->height() * circuit->scale());
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

void CircuitWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::HighQualityAntialiasing);

  circuit->draw(painter);
}

void CircuitWidget::mouseMoveEvent(QMouseEvent *event)
{
  event = new QMouseEvent(event->type(), event->pos(), Qt::NoButton, Qt::NoButton, 0);

  circuit->mouseEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent *event)
{
  int x = event->x();
  int y = event->y();

  if(x < 0 || y < 0 || y > height() || x > width())
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

void CircuitWidget::keyReleaseEvent(QKeyEvent *event)
{
  circuit->keyReleaseEvent(event);
  QWidget::keyReleaseEvent(event);
}

#undef selectedTool
