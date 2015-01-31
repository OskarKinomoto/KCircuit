#include "circuitwidget.h"
#include "mainwindow.h"
#define selectedTool MainWindow::selectedTool

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

void CircuitWidget::updateSize()
{
  this->resize(circuit->width() * circuit->scale(), circuit->height() * circuit->scale());
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
  int x = event->x();
  int y = event->y();

  if(x < 0 || y < 0 || y > height() || x > width())
    {

    }
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

void CircuitWidget::keyPressEvent(QKeyEvent *event)
{
  circuit->keyPressEvent(event);
  QWidget::keyPressEvent(event);
}

#undef selectedTool
