#include "circuitscrollarea.h"
#include "mainwidget.h"

//MainWidget * MainWidget::MAIN_WIDGET = nullptr;

CircuitScrollArea::CircuitScrollArea(Circuit *circuit, QTabWidget *parent) : QScrollArea(parent)
{
  this->setBackgroundRole(QPalette::Dark);
  this->setAlignment(Qt::AlignCenter);

  circuitWidget = new CircuitWidget(circuit, this);
  this->setWidget(circuitWidget);
  circuit->setWidget(circuitWidget);

#ifdef __linux__

  if(QApplication::style()->objectName() == "breeze")
    {
      corner = new QWidget();
      corner->setAutoFillBackground(true);
      corner->setBackgroundRole(QPalette::Base);
    }
  this->verticalScrollBar()->setAutoFillBackground(true);
  this->horizontalScrollBar()->setAutoFillBackground(true);
  this->recolorScrollBars();
#endif

  parentTabWidget = parent;

}

CircuitScrollArea::~CircuitScrollArea()
{

}
#ifdef __linux__
void CircuitScrollArea::recolorScrollBars()
{
  bool wh = this->verticalScrollBar()->maximum() != 0 && this->horizontalScrollBar()->maximum() != 0;

  this->verticalScrollBar()->setBackgroundRole(wh ? QPalette::Base : QPalette::Dark);
  this->horizontalScrollBar()->setBackgroundRole(wh ? QPalette::Base : QPalette::Dark);
  this->setCornerWidget(wh ? corner : nullptr);
}
#endif
void CircuitScrollArea::setMouseTrackingCircuit(bool enable)
{
  this->circuitWidget->setMouseTracking(enable);
}

void CircuitScrollArea::setTitle(QString s)
{
  MainWidget::MAIN_WIDGET->setName(s, this);
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
      this->circuitWidget->forceMouseMoveEvent();
    }
}

