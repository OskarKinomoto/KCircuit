#include "circuitmodel.h"

#include <QDataStream>
#include "tabwidget.h"
#include "global.h"

#include "listobjects.h"

CircuitModel::CircuitModel(QString Path) {
  if (!QFile::exists(Path))
    throw QString("File doesn't exist!");
  path = Path;

  QFile file(path);
  name = QFileInfo(file).fileName();

  file.open(QIODevice::ReadOnly);
  if (!file.isReadable()) {
    throw QString("File is not readable!");
  }

  QDataStream in(&file);

  quint32 magick;
  in >> magick;
  if (magick != K::magicknumber)
    throw QString("Wrong file type!");

  quint16 version;
  in >> version;
  if (version != K::objectversion)
    throw QString("Unsuported version of file.");

  in >> widthG;
  in >> heightG;

  in >> ID;

  quint32 size;
  in >> size;
  quint32 type;

  for (quint32 i = 0; i < size; ++i) {
    in >> type;
    switch (type) {
    case K::objectType::RESISTOR:
      objects.push_back(new ObjectResistor(in));
      break;
    case K::objectType::WIRE:
      objects.push_back(new ObjectWire(in));
      break;
    case K::objectType::CAPACITOR:
      objects.push_back(new ObjectCapacitor(in));
      break;
    case K::objectType::COIL:
      objects.push_back(new ObjectCoil(in));
      break;
    default:
      throw QString("Type not implemented");
    }
  }
}

CircuitModel::CircuitModel(CircuitSettings s) {
  ID = 0;
  path = "";
  name = "new";
  widthG = s.widthG;
  heightG = s.heightG;
}

CircuitModel::~CircuitModel() {
  delete history;
  for (auto itr : objects) {
    delete itr;
  }
}

QSize CircuitModel::size() {
  return {int(widthG * K::grid * scale), int(heightG * K::grid * scale)};
}

bool CircuitModel::mouseMoved(QPoint p) {
  if (drawing) {
    return drawing->move(p);
  } else if (tool != K::tool::POINTER) {
    newDrawing(p);
    return true;
  }
  return false;
}

void CircuitModel::mouseDraged(QPoint d) {
  if (current)
    current->moveBy(d);
}

void CircuitModel::scaleUp() {
  if (scale < 3)
    scale *= 1.2;
}

void CircuitModel::scaleDown() {
  if (scale > 0.5)
    scale /= 1.2;

  this->exportToPng("/home/oskar/test.png");
}

bool CircuitModel::rotate45() {
  angle += 45;
  angle %= 360;
  if (drawing)
    return drawing->rotate45();
  if (current) {
    history->add(new HistoryNodeRotate(current, 45));
    setModyfied();
    return current->rotate45();
  }
  return false;
}

bool CircuitModel::rotate90() {
  angle += 90;
  angle %= 360;
  if (drawing)
    return drawing->rotate90();
  if (current) {
    history->add(new HistoryNodeRotate(current, 90));
    setModyfied();
    return current->rotate90();
  }
  return false;
}

bool CircuitModel::rotate315() {
  angle += 315;
  angle %= 360;
  if (drawing)
    return drawing->rotate315();
  if (current) {
    history->add(new HistoryNodeRotate(current, 315));
    setModyfied();
    return current->rotate315();
  }
  return false;
}

bool CircuitModel::rotate270() {
  angle += 270;
  angle %= 360;
  if (drawing)
    return drawing->rotate270();
  if (current) {
    history->add(new HistoryNodeRotate(current, 270));
    setModyfied();
    return current->rotate270();
  }
  return false;
}

void CircuitModel::exportToPng(QString path) {
  auto scaleTmp = scale;
  scale = 1;

  K::gs = K::grid;

  QImage pixmap(size().width(), size().height(), QImage::Format_ARGB32);
  pixmap.fill(Qt::white);
  QPainter p(&pixmap);

  for (auto itr = objects.begin(); itr != objects.end(); itr++) {
    if (*itr == drawing)
      p.setPen(drawingPen);
    else if (*itr == current)
      p.setPen(currentPen);
    else
      p.setPen(stdPen);
    (*itr)->draw(p);
  }

  QImage croped = pixmap.copy(this->getRectangle(&pixmap));
  croped.save(path);
  scale = scaleTmp;
}

void CircuitModel::paint(QPainter &p) {
  K::gs = K::grid * scale;
  if (K::showGrid)
    this->paintGrid(p);

  for (auto itr = objects.begin(); itr != objects.end(); itr++) {
    if (*itr == drawing)
      p.setPen(drawingPen);
    else if (*itr == current)
      p.setPen(currentPen);
    else
      p.setPen(stdPen);
    (*itr)->draw(p);
  }
}

void CircuitModel::paintGrid(QPainter &p) {
  p.save();
  {
    QPen pen(Qt::darkGreen);
    p.setPen(pen);
    auto s = this->size();
    int w = s.width();
    int h = s.height();
    for (float i = K::gs; i < w; i += K::gs)
      for (float j = K::gs; j < h; j += K::gs)
        p.drawPoint(i, j);
  }
  p.restore();
}

void CircuitModel::destroyDrawing() {
  if (drawing) {
    delete drawing;
    objects.remove(drawing);
    drawing = nullptr;
    --ID;
  }
}

void CircuitModel::release() {
  if (current) {
    QPoint tmp = current->acceptMove();
    if (tmp != QPoint(0, 0)) {
      history->add(new HistoryNodeMove(current, tmp));
      setModyfied();
    }
  }
  if (!drawing && tool == K::tool::WIRE) {
    objects.push_back(new ObjectWire(p, ++ID));
    drawing = objects.back();
  }
  if (drawing && drawing->release())
    this->drawed();
}

bool CircuitModel::press(QMouseEvent *e) {
  if (tool != K::tool::POINTER)
    return (current = nullptr, false);
  for (auto itr : objects)
    if (itr->isPointOverObject(e->pos()))
      return (current = itr, listObjects->setCurrent(current),
              rightWidget->setObjectSettings(
                  current->settings(static_cast<Circuit *>(this))),
              e->button() == Qt::RightButton);
  return (current = nullptr, listObjects->setCurrent(nullptr),
          rightWidget->setObjectSettings(nullptr), false);
}

void CircuitModel::newDrawing(QPoint p) {
  bool draw = true;
  switch (tool) {
  case K::tool::RESISTOR:
    objects.push_back(new ObjectResistor(p, angle, ++ID));
    break;
  case K::tool::WIRE:
    draw = false;
    this->p = p;
    break;
  case K::tool::CAPACITOR:
    objects.push_back(new ObjectCapacitor(p, angle, ++ID));
    break;
  case K::tool::COIL:
    objects.push_back(new ObjectCoil(p, angle, ++ID));
    break;
  default:
    qDebug() << "not implemented" << __FILE__ << __LINE__;
    draw = false;
    break;
  }
  if (draw)
    drawing = objects.back();
}

void CircuitModel::drawed() {
  history->add(new HistoryNodeNew(drawing));
  setModyfied();
  setCurrent(drawing);
  drawing = nullptr;
  listObjects->load();
  listObjects->setCurrent(current);
}

void CircuitModel::initPens() {
  stdPen = QPen(K::baseC); //#4d4d4d
  stdPen.setWidth(2);
  drawingPen = QPen(QColor::fromRgb(244, 119, 80)); //#f47750
  drawingPen.setWidth(2);
  currentPen = QPen(QColor::fromRgb(29, 153, 243)); //#1d99f3
  currentPen.setWidth(2);
}

void CircuitModel::setModyfied() {
  if (!modyfied) {
    modyfied = true;
    updateTitle();
  }
}

void CircuitModel::doubleClick() {
  if (drawing && tool == K::tool::WIRE) {
    static_cast<ObjectResistor *>(drawing)->doubleClick();
    this->drawed();
  }
}

void CircuitModel::updateTitle() {
  QString tmp;
  if (modyfied)
    tmp += "*";
  tmp += name;
  K::tabWidget->changeTitle(tmp, index);
}

void CircuitModel::addObject(ObjectAbstract *o) {
  objects.push_back(o);
  setModyfied();
  listObjects->load();
}

void CircuitModel::removeObject(ObjectAbstract *o, bool history) {
  if (history)
    this->history->add(new HistoryNodeRemove(o));
  objects.remove(o);
  setModyfied();
  listObjects->load();
}

void CircuitModel::removeCurrent() {
  this->removeObject(current, true);
  current = nullptr;
}

void CircuitModel::saveAs(QString _path) {
  if (QFileInfo(_path).suffix() != "ktc")
    _path += ".ktc";
  path = _path;
  name = QFileInfo(path).fileName();
  save();
}

void CircuitModel::save() {
  QFile file(path);
  file.open(QIODevice::WriteOnly);

  if (!file.isWritable()) {
    path = "";
    name = "unwritable";
    updateTitle();
    throw QString("File is not writable!");
  }

  QDataStream out(&file);
  out << K::magicknumber;
  out << K::objectversion;

  // size
  out << widthG;
  out << heightG;

  out << ID;
  qDebug() << ID;

  out << quint32(objects.size());

  for (auto itr = objects.begin(); itr != objects.end(); ++itr) {
    if (*itr != drawing)
      (*itr)->save(out);
  }

  modyfied = false;
  updateTitle();
}

bool CircuitModel::hasPath() { return path != ""; }

bool CircuitModel::isModyfied() { return modyfied; }

std::list<ObjectAbstract *> &CircuitModel::list() { return objects; }

void CircuitModel::setList(ListObjects *l) { listObjects = l; }

void CircuitModel::setRightWidget(RightWidget *r) { rightWidget = r; }

void CircuitModel::setCurrent(ObjectAbstract *o) {
  current = o;
  if (o) {
    rightWidget->setObjectSettings(o->settings(static_cast<Circuit *>(this)));
  }
}

QRect CircuitModel::getRectangle(QImage *p) {
  int r = 0;
  int l = p->width();
  int t = 0;
  int b = 0;
  bool e1 = true;
  for (int i = 0; i < p->height(); ++i) {
    bool e2 = true;
    for (int j = 0; j < p->width(); ++j) {
      if (QColor().fromRgb(p->pixel(j, i)) != Qt::white) {
        r = std::max(j, r);
        if (e2) {
          l = std::min(j - 1, l);
        }
        e2 = false;
        e1 = false;
      }
    }
    if (e2 && e1) {
      t = i + 1;
    }
    if (!e2)
      b = i;
  }
  int MARGIN = 50;
  b = (b + MARGIN > p->height() ? p->height() : b + MARGIN);
  t = (t - MARGIN < 0 ? 0 : t - MARGIN);
  r = (r + MARGIN > p->width() ? p->width() : r + MARGIN);
  l = (l - MARGIN < 0 ? 0 : l - MARGIN);
  return QRect(l, t, r - l, b - t);
}
