#include "circuit.h"

Circuit::Circuit(CircuitSettings settings)
    : CircuitView(), CircuitModel(settings) {
  this->init();
}

Circuit::Circuit(QString path) : CircuitView(), CircuitModel(path) {
  this->init();
}

Circuit::~Circuit() {}

void Circuit::setTool(K::tool::tool t) {
  angle = 0;
  tool = t;
}

void Circuit::rotate45() {
  if (CircuitModel::rotate45())
    this->update();
}

void Circuit::rotate90() {
  if (CircuitModel::rotate90())
    this->update();
}

void Circuit::rotate270() {
  if (CircuitModel::rotate270())
    this->update();
}

void Circuit::rotate315() {
  if (CircuitModel::rotate315())
    this->update();
}

bool Circuit::undo() {
  history->undo();
  this->update();
  return history->forwardable();
}

bool Circuit::redo() {
  history->redo();
  this->update();
  return history->backable();
}

void Circuit::scale(bool s) {
  if (s)
    scaleUp();
  else
    scaleDown();
  updateSize();
}

void Circuit::paint(QPaintEvent *p) {
  visibleRectangle = p->rect();
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::HighQualityAntialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);

  CircuitModel::paint(painter);
}

void Circuit::mouseMoved(QPoint p) {
  if (CircuitModel::mouseMoved(p))
    this->update();
}

void Circuit::mouseDraged(QPoint d) {
  CircuitModel::mouseDraged(d);
  this->update();
}

void Circuit::leave() { this->destroyDrawing(); }

void Circuit::release() {
  CircuitModel::release();
  this->update();
}

void Circuit::press(QMouseEvent *e) {
  if (CircuitModel::press(e))
    this->showContextMenu(e->pos());
  this->update();
}

void Circuit::removeCurrent() {
  CircuitModel::removeCurrent();
  this->update();
}

void Circuit::showContextMenu(const QPoint &pos) {
  QPoint globalPos = this->mapToGlobal(pos);
  contextMenu.exec(globalPos);
}

void Circuit::doubleClick() {
  CircuitModel::doubleClick();
  this->update();
}

void Circuit::updateSize() {
  this->setSize(CircuitModel::size());
  emit updatedSize();
}

void Circuit::init() {
  updateSize();
  initPens();
  history = new History(this);

  connect(this, SIGNAL(paint(QPaintEvent *)), this, SLOT(paint(QPaintEvent *)));
  connect(this, SIGNAL(mouseMove(QPoint)), this, SLOT(mouseMoved(QPoint)));
  connect(this, SIGNAL(leave()), this, SLOT(leave()));
  connect(this, SIGNAL(release()), this, SLOT(release()));
  connect(this, SIGNAL(press(QMouseEvent *)), this, SLOT(press(QMouseEvent *)));

  connect(this, SIGNAL(mouseDrag(QPoint)), this, SLOT(mouseDraged(QPoint)));

  connect(this, SIGNAL(doubleClick()), this, SLOT(doubleClick()));

  removeCurrentA =
      new QAction(QIcon::fromTheme("window-close"), tr("Remove"), nullptr);
  connect(removeCurrentA, SIGNAL(triggered()), this, SLOT(removeCurrent()));
  contextMenu.addActions({removeCurrentA});
}
