#include "objectsettingsresistor.h"

#include <QtWidgets>
#include "objectresistor.h"
#include "circuit.h"
#include "listobjects.h"

ObjectSettingsResistor::ObjectSettingsResistor(ObjectResistor *resistor,
                                               Circuit *c)
    : ObjectSettingsAbstract(c) {
  r = resistor;

  name = new QLineEdit(r->getName());
  l->addRow(tr("Name"), name);
  connect(name, SIGNAL(textEdited(QString)), this, SLOT(nameEdited(QString)));

  label = new QLineEdit(r->getLabel());
  l->addRow(tr("Label"), label);
  connect(label, SIGNAL(textEdited(QString)), this, SLOT(labelEdited(QString)));

  type = new QComboBox();
  type->addItem(tr("Resistor"), 0);
  type->addItem(tr("Potentiometr"), 1);
  type->addItem(tr("Decade"), 2);
  type->addItem(tr("Thermistor"), 3);
  type->setCurrentIndex(r->getTyp());
  l->addRow(tr("Type"), type);
  connect(type, SIGNAL(activated(int)), this, SLOT(typeEdited(int)));

  color = new ColorComboBox();
  l->addRow(tr("Color"), color);
  connect(color, SIGNAL(colorChanged(QColor)), this, SLOT(colorEdited(QColor)));
  if (r->isColorSet())
    color->setCurrentIndex(color->findData(r->getColor()));
}

ObjectSettingsResistor::~ObjectSettingsResistor() {}

void ObjectSettingsResistor::nameEdited(QString t) {
  r->setName(t);
  c->listObjects->load();
  this->c->setModyfied();
}

void ObjectSettingsResistor::labelEdited(QString t) {
  r->setLabel(t);
  c->update();
  this->c->setModyfied();
}

void ObjectSettingsResistor::typeEdited(int i) {
  r->setTyp(i);
  c->update();
  this->c->setModyfied();
}

void ObjectSettingsResistor::colorEdited(QColor c) {
  r->setColor(c);
  this->c->update();
  this->c->setModyfied();
}
