#include "objectsettingsabstract.h"

ObjectSettingsAbstract::ObjectSettingsAbstract(Circuit *circuit) : QWidget(nullptr)
{
  c = circuit;
  this->setMinimumHeight(200);
  l = new QFormLayout();
  this->setLayout(l);
}

ObjectSettingsAbstract::~ObjectSettingsAbstract()
{

}

