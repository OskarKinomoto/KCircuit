#include "circuitscrollarea.h"


CircuitScrollArea::CircuitScrollArea(Circuit *circuit, QWidget *parent) : QScrollArea(parent)
{
  this->setBackgroundRole(QPalette::Dark);
  this->setAlignment(Qt::AlignCenter);

  circuitWidget = new CircuitWidget(circuit);
  this->setWidget(circuitWidget);
  circuit->setWidget(circuitWidget);

  corner = new QWidget();
  corner->setAutoFillBackground(true);
  corner->setBackgroundRole(QPalette::Base);

  //Scrollbars coloring
  this->verticalScrollBar()->setAutoFillBackground(true);
  this->horizontalScrollBar()->setAutoFillBackground(true);
  this->recolorScrollBars();

  parentTabWidget = (QTabWidget*)this->parentWidget();

  //centering


}

CircuitScrollArea::~CircuitScrollArea()
{

}

void CircuitScrollArea::recolorScrollBars()
{
  bool w = this->parentWidget()->width() - this->verticalScrollBar()->width() - 5 < this->circuitWidget->width();
  bool h = this->parentWidget()->height() - this->horizontalScrollBar()->height() - 5 < this->circuitWidget->height();
  bool wh = w && h;

  this->verticalScrollBar()->setBackgroundRole(wh ? QPalette::Base : QPalette::Dark);
  this->horizontalScrollBar()->setBackgroundRole(wh ? QPalette::Base : QPalette::Dark);
  this->setCornerWidget(wh ? corner : nullptr);
}

void CircuitScrollArea::setMouseTrackingCircuit(bool enable)
{
  this->circuitWidget->setMouseTracking(enable);
}

void CircuitScrollArea::setTitle(QString s)
{
  parentTabWidget->setTabText(parentTabWidget->indexOf(this), s);
}

void CircuitScrollArea::resizeEvent(QResizeEvent *event)
{
  this->recolorScrollBars();
  QScrollArea::resizeEvent(event);
}

void CircuitScrollArea::wheelEvent(QWheelEvent *event)
{
  if(event->modifiers() == Qt::CTRL)
    {
      ///TODO time :)
      delta += event->delta();
      if(delta >= 120)
        {
          this->circuitWidget->scaleUp();
          delta = 0;
        }
      else if(delta <= -120)
        {
          this->circuitWidget->scaleDown();
          delta = 0;
        }
    }
  else
    {
      QScrollArea::wheelEvent(event);
    }
}

