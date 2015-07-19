#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include "rightwidgetview.h"

class RightWidget : public RightWidgetView {
public:
  RightWidget(Circuit *circuit);
  ~RightWidget();
};

#endif // RIGHTWIDGET_H
