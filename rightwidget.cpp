#include "rightwidget.h"
#include "circuit.h"

RightWidget::RightWidget(Circuit * circuit) : RightWidgetView(circuit)
{
  circuit->setRightWidget(this);
}

RightWidget::~RightWidget()
{

}

