#include "objectbase.h"

ObjectBase::ObjectBase(QPoint p, quint16 a, K::objectType t, quint32 id)
    : ObjectAbstract(t, id) {
  point = QPoint(p.x() / K::gs + .5, p.y() / K::gs + .5);
  angle = a;
}

ObjectBase::ObjectBase(QDataStream &in, K::objectType t)
    : ObjectAbstract(t, in) {
  in >> point;
  in >> angle;
  in >> name;
  in >> colorB;
  if (colorB)
    in >> color;
}

ObjectBase::~ObjectBase() {}

void ObjectBase::draw(QPainter &p) {
  p.save();
  p.translate(point * K::gs);
  p.translate(moved);
  p.rotate(angle);
  if (colorB && p.pen().color() == K::baseC) {
    QPen pen = p.pen();
    pen.setColor(color);
    p.setPen(pen);
  }
  drawObject(p);
  p.restore();
}

void ObjectBase::save(QDataStream &out) {
  out << (quint32) this->type;
  out << ID;
  out << point;
  out << angle;
  out << name;
  out << colorB;
  if (colorB)
    out << color;
  saveSettings(out);
}

bool ObjectBase::move(QPoint p) {
  p = QPoint(p.x() / K::gs + .5, p.y() / K::gs + .5);
  if (point == p)
    return false;
  point = p;
  return true;
}

bool ObjectBase::release() { return true; }

bool ObjectBase::rotate45() {
  angle += 45;
  angle %= 360;
  return true;
}

bool ObjectBase::rotate90() {
  angle += 90;
  angle %= 360;
  return true;
}

bool ObjectBase::rotate315() {
  angle += 315;
  angle %= 360;
  return true;
}

bool ObjectBase::rotate270() {
  angle += 270;
  angle %= 360;
  return true;
}

void ObjectBase::moveBy(QPoint d) { moved += d; }

void ObjectBase::moveByGS(QPoint gs) {
  point += gs;
  moved = QPoint(0, 0);
}

QPoint ObjectBase::acceptMove() {
  QPoint tmp = moved / K::gs;
  point += tmp;
  moved = QPoint(0, 0);
  return tmp;
}

void ObjectBase::dropMove() { moved = QPoint(0, 0); }

void ObjectBase::setColor(QColor c) {
  if (c == K::baseC) {
    colorB = false;
    color = QColor();
  } else {
    colorB = true;
    color = c;
  }
}

QColor ObjectBase::getColor() {
  if (colorB)
    return this->color;
  QColor color;
  color.setNamedColor("#4d4d4d");
  return color;
}

bool ObjectBase::isColorSet() { return colorB; }

void ObjectBase::doubleClick() {}
