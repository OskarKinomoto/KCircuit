#include "objectwire.h"

ObjectWire::ObjectWire(QPoint p, quint32 id) : ObjectAbstract(K::WIRE, id) {
  QPoint tmp(p.x() / K::gs + .5, p.y() / K::gs + .5);
  points.reserve(4);
  points.push_back(tmp);
  points.push_back(tmp);
  typ.push_back(false);
  typ.push_back(false);
  name = "Wire " + QString::number(id);
  mode = K::wireMode;
}

ObjectWire::ObjectWire(QDataStream &in) : ObjectAbstract(K::WIRE, in) {
  quint16 num;
  in >> num;
  points.reserve(num);
  typ.reserve(num);
  for (int i = 0; i < num; ++i) {
    QPoint tmp;
    in >> tmp;
    points.push_back(tmp);
  }
  for (int i = 0; i < num; ++i) {
    bool tmp;
    in >> tmp;
    typ.push_back(tmp);
  }
  quint8 wmode;
  in >> wmode;
  mode = K::WIRE_MODE(wmode);
}

ObjectWire::~ObjectWire() {}

void ObjectWire::draw(QPainter &p) {
  p.save();
  p.translate(moved);

  switch (mode) {
  case K::WIRE_SHORTEST:
    for (auto itr = points.begin(), itr2 = itr + 1; itr2 < points.end();
         ++itr, ++itr2)
      p.drawLine(itr->x() * K::gs, itr->y() * K::gs, itr2->x() * K::gs,
                 itr2->y() * K::gs);
    break;

  case K::WIRE_TAXI:
    int i = 1;
    for (auto itr = points.begin(), itr2 = itr + 1; itr2 < points.end();
         ++itr, ++itr2, ++i)
      if (itr->x() == itr2->x() || itr->y() == itr2->y())
        p.drawLine(itr->x() * K::gs, itr->y() * K::gs, itr2->x() * K::gs,
                   itr2->y() * K::gs);
      else {
        int midX = typ[i] ? itr->x() : itr2->x();
        int midY = typ[i] ? itr2->y() : itr->y();
        p.drawLine(itr->x() * K::gs, itr->y() * K::gs, midX * K::gs,
                   midY * K::gs),
            p.drawLine(midX * K::gs, midY * K::gs, itr2->x() * K::gs,
                       itr2->y() * K::gs);
      }

    break;
  }
  p.restore();
}

void ObjectWire::save(QDataStream &out) {
  out << quint32(K::WIRE);
  out << ID;
  out << quint16(points.size());
  for (QPoint &point : points)
    out << point;

  for (bool b : typ)
    out << b;
  out << quint8(mode);
}

bool ObjectWire::move(QPoint p) {
  QPoint tmp(p.x() / K::gs + .5, p.y() / K::gs + .5);
  if (points.back() == tmp)
    return false;
  points.back() = tmp;
  return true;
}

bool ObjectWire::release() {
  if (points[points.size() - 1] != points[points.size() - 2])
    points.push_back(points.back()), typ.push_back(typ.back());

  return false;
}

bool ObjectWire::isPointOverObject(QPointF p) {
  p /= K::gs;

  switch (mode) {
  case K::WIRE_SHORTEST:

    for (size_t i = 0, j = 1; j < points.size(); ++i, ++j)
      if (isPointOverWirePart(points.at(i), points.at(j), p, 0.15))
        return true;

    break;

  case K::WIRE_TAXI:
    for (size_t i = 0, j = 1; j < points.size(); ++i, ++j)
      if (points.at(i).x() == points.at(j).x() ||
          points.at(i).y() == points.at(j).y()) {
        if (isPointOverWirePart(points.at(i), points.at(j), p, 0.15))
          return true;
      } else {
        QPoint mid(points.at(typ.at(j) ? i : j).x(),
                   points.at(typ.at(j) ? j : i).y());
        if (isPointOverWirePart(points.at(i), mid, p, 0.15))
          return true;
        if (isPointOverWirePart(mid, points.at(j), p, 0.15))
          return true;
      }
  }
  return false;
}

void ObjectWire::moveBy(QPoint d) { moved += d; }

void ObjectWire::moveByGS(QPoint gs) {
  for (QPoint &point : points)
    point += gs;
  moved = QPoint(0, 0);
}

QPoint ObjectWire::acceptMove() {
  QPoint tmp = moved / K::gs;
  for (QPoint &point : points)
    point += tmp;
  moved = QPoint(0, 0);
  return tmp;
}

void ObjectWire::dropMove() {}

void ObjectWire::doubleClick() {
  points.pop_back();
  typ.pop_back();
}

bool ObjectWire::rotate90() {
  typ[typ.size() - 1] = !typ.back();
  qDebug() << typ.back();
  return true;
}

ObjectSettingsAbstract *ObjectWire::settings(Circuit *) { return nullptr; }

bool ObjectWire::isPointOverWirePart(QPoint &a, QPoint &b, QPointF &c,
                                     float dist) {
  int px = b.x() - a.x();
  int py = b.y() - a.y();

  int tmp = px * px + py * py;

  float u = (c.x() - a.x()) * px + (c.y() - a.y()) * py;
  u /= tmp;

  if (u > 1)
    u = 1;
  else if (u < 0)
    u = 0;

  float tx = a.x() + u * px;
  float ty = a.y() + u * py;

  float dx = tx - c.x();
  float dy = ty - c.y();

  return dx * dx + dy * dy <= dist;
}
