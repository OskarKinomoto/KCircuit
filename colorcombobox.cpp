#include "colorcombobox.h"

#include <QPixmap>
#include <QRgb>

ColorComboBox::ColorComboBox() {
  this->addColor("#4d4d4d");
  this->addColor("#da4453");
  this->addColor("#5077f4");
  this->addColor("#1df399");
  this->addColor("#fdbc4b");
  this->addColor("#2ecc71");
  this->addColor("#712ecc");
  connect(this, SIGNAL(currentIndexChanged(int)), this,
          SLOT(currentChanged(int)));
}

ColorComboBox::~ColorComboBox() {}

void ColorComboBox::addColor(QString name) {
  QColor color;
  color.setNamedColor(name);
  QPixmap pixmap(20, 20);
  pixmap.fill(color);
  this->addItem(QIcon(pixmap), "", color);
}

void ColorComboBox::currentChanged(int i) {
  emit colorChanged(this->itemData(i).value<QColor>());
}
