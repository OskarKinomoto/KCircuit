#include "objectcoil.h"

ObjectCoil::ObjectCoil(QPoint p, quint16 a, quint32 id)
    : ObjectBase(p, a, K::COIL, id) {
  name = "Coil " + QString::number(id);
}

ObjectCoil::ObjectCoil(QDataStream &in) : ObjectBase(in, K::COIL) {
  loadSettings(in);
}

ObjectCoil::~ObjectCoil() {
  // if(labelImg) delete labelImg;
}

bool ObjectCoil::isPointOverObject(QPointF p) {
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

ObjectSettingsAbstract *ObjectCoil::settings(Circuit *c) { return nullptr; }

void ObjectCoil::drawObject(QPainter &p) {
  p.drawArc(-2.5 * K::gs, -.75 * K::gs, K::gs, 1.5 * K::gs, 0, 180 * 16);
  p.drawArc(-1.5 * K::gs, -.75 * K::gs, K::gs, 1.5 * K::gs, 0, 180 * 16);
  p.drawArc(-.5 * K::gs, -.75 * K::gs, K::gs, 1.5 * K::gs, 0, 180 * 16);
  p.drawArc(.5 * K::gs, -.75 * K::gs, K::gs, 1.5 * K::gs, 0, 180 * 16);
  p.drawArc(1.5 * K::gs, -.75 * K::gs, K::gs, 1.5 * K::gs, 0, 180 * 16);
  if (angle % 90) {
    p.drawLine(-2 * K::sqrt2 * K::gs, 0, -2.5 * K::gs, 0);
    p.drawLine(2 * K::sqrt2 * K::gs, 0, 2.5 * K::gs, 0);
  } else {
    p.drawLine(-3 * K::gs, 0, -2.5 * K::gs, 0);
    p.drawLine(3 * K::gs, 0, 2.5 * K::gs, 0);
  }
}

void ObjectCoil::saveSettings(QDataStream &out) {
  // out << label;
  // out << quint8(typ);
}

void ObjectCoil::loadSettings(QDataStream &in) {
  // in >> label;
  quint8 tmp;
  in >> tmp;
  // typ = TYPE(tmp);
}

ObjectCoil::TYPE ObjectCoil::getTyp() const {
  // return typ;
}

void ObjectCoil::setTyp(int value) {
  // typ = ObjectCoil::TYPE(value);
}

QString ObjectCoil::getLabel() const {
  // return label;
  return QString();
}

void ObjectCoil::setLabel(const QString &value) {
  // label = value;
  // gsRendered = 0;
}
