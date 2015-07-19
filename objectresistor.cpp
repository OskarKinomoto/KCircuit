#include "objectresistor.h"

#include "objectsettingsresistor.h"

#include "textpainter.h"

ObjectResistor::ObjectResistor(QPoint p, quint16 a, quint32 id)
    : ObjectBase(p, a, K::RESISTOR, id) {
  name = "Resistor " + QString::number(id);
}

ObjectResistor::ObjectResistor(QDataStream &in) : ObjectBase(in, K::RESISTOR) {
  loadSettings(in);
}

ObjectResistor::~ObjectResistor() {
  if (labelImg)
    delete labelImg;
}

bool ObjectResistor::isPointOverObject(QPointF p) {
  p /= K::gs;
  p -= point;
  float x = p.x();
  float y = p.y();
  auto d = K::degrees::angle2enum(angle);
  float x2 = x * K::degrees::cosine[d] + y * K::degrees::sine[d];
  float y2 = x * K::degrees::sine[d] - y * K::degrees::cosine[d];
  x2 = x2 < 0 ? -x2 : x2;
  y2 = y2 < 0 ? -y2 : y2;

  if (x2 <= 3 && y2 <= .5)
    return true;
  else if (x2 <= 2 && y2 <= 1)
    return true;
  return false;
}

ObjectSettingsAbstract *ObjectResistor::settings(Circuit *c) {
  return new ObjectSettingsResistor(this, c);
}

void ObjectResistor::drawObject(QPainter &p) {
  if (angle % 90) // angle = 45
  {
    p.drawLine(-2 * K::sqrt2 * K::gs, 0, -2 * K::gs, 0);
    p.drawLine(2 * K::sqrt2 * K::gs, 0, 2 * K::gs, 0);
  } else // angle = 90
  {
    p.drawLine(-3 * K::gs, 0, -2 * K::gs, 0);
    p.drawLine(3 * K::gs, 0, 2 * K::gs, 0);
  }
  p.drawRect(-2 * K::gs, -.75 * K::gs, 4 * K::gs, 1.5 * K::gs);

  if (typ == POTENTIOMETR) {
    p.drawLine(0, -2 * K::gs, 0, -.75 * K::gs);
    p.drawLine(.5 * K::gs, -1.25 * K::gs, 0, -.75 * K::gs);
    p.drawLine(-.5 * K::gs, -1.25 * K::gs, 0, -.75 * K::gs);
  } else if (typ == DECADE) {
    p.drawLine(-1.5 * K::gs, 1.5 * K::gs, 1.5 * K::gs, -1.5 * K::gs);
    p.drawLine(1.8 * K::gs, -1.2 * K::gs, 1.2 * K::gs, -1.8 * K::gs);
  } else if (typ == THREMISTOR) {
    p.drawLine(-1 * K::gs, 1.25 * K::gs, 2 * K::gs, -1.5 * K::gs);
    p.drawLine(-1 * K::gs, 1.25 * K::gs, -2 * K::gs, 1.25 * K::gs);
  }

  // Label
  if (label != "") {
    TextPainter tmp(label, K::gs / K::grid);
    if (gsRendered != K::gs) {
      if (labelImg)
        delete labelImg;
      labelImg = tmp.getCropedImage();
      gsRendered = K::gs;
    }
    p.rotate(-angle);
    switch (angle) {
    case 0:
      p.drawImage(-labelImg->width() / 2, -labelImg->height() / 2 + 2 * K::gs,
                  *labelImg);
      break;
    case 180:
      p.drawImage(-labelImg->width() / 2, -labelImg->height() / 2 - 2 * K::gs,
                  *labelImg);
      break;
    case 90:
      p.drawImage(-labelImg->width() - K::gs, -labelImg->height() / 2,
                  *labelImg);
      break;
    case 270:
      p.drawImage(K::gs, -labelImg->height() / 2, *labelImg);
      break;
    case 45:
      p.drawImage(-labelImg->width() - K::gs, labelImg->height() / 2 - K::gs,
                  *labelImg);
      break;
    case 135:
      p.drawImage(-labelImg->width() - K::gs, -labelImg->height() / 2 - K::gs,
                  *labelImg);
      break;
    case 225:
      p.drawImage(K::gs, -labelImg->height() / 2 - K::gs, *labelImg);
      break;
    case 315:
      p.drawImage(K::gs, labelImg->height() / 2 - K::gs, *labelImg);
      break;
    }
  }
}

void ObjectResistor::saveSettings(QDataStream &out) {
  out << label;
  out << quint8(typ);
}

void ObjectResistor::loadSettings(QDataStream &in) {
  in >> label;
  quint8 tmp;
  in >> tmp;
  typ = TYPE(tmp);
}

ObjectResistor::TYPE ObjectResistor::getTyp() const { return typ; }

void ObjectResistor::setTyp(int value) { typ = ObjectResistor::TYPE(value); }

QString ObjectResistor::getLabel() const { return label; }

void ObjectResistor::setLabel(const QString &value) {
  label = value;
  gsRendered = 0;
}
