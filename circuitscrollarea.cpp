#include "circuitscrollarea.h"

CircuitScrollArea::CircuitScrollArea()
{
  this->setBackgroundRole(QPalette::Dark);
  this->setAlignment(Qt::AlignCenter);
}

CircuitScrollArea::~CircuitScrollArea()
{

}

void CircuitScrollArea::wheelEvent(QWheelEvent *event)
{
  CircuitRenderArea * render = (CircuitRenderArea*)(this->widget());

  if(event->modifiers() == Qt::CTRL)
  {
    //render->setScale(render->scale() + (event->delta() > 0 ? 0.1 : -0.1));
      render->setScale(render->scale() + (event->delta() / 250.0), event->x(), event->y());
  }
  else
  {
    QScrollArea::wheelEvent(event);
  }

}

