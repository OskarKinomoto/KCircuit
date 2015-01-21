#include "circuitrenderarea.h"

CircuitRenderArea::CircuitRenderArea(QScrollArea *parent) : QWidget(parent)
{
  p = parent;
  l=r=b=t=0;
  updateLRTB();
  _scale = 1;
  this->resize(width(),height());
  this->setAutoFillBackground(true);
  this->setBackgroundRole(QPalette::Base);
  i = 0;

  loadRenderHint();
}

void CircuitRenderArea::updateLRTB(){
  uint32_t w2 = p->width() >> 1;
  uint32_t h2 = p->height() >> 1;
  t = h2*3;
  b = h2*3;
  l = w2*3;
  r = w2*3;
}

void CircuitRenderArea::updateSize()
{
  updateLRTB();
  resize(width(), height());
}

int CircuitRenderArea::width()
{
  return((l+r));
}

int CircuitRenderArea::height()
{
  return((t+b));
}

void CircuitRenderArea::loadRenderHint()
{
  QSettings set;
  set.beginGroup(QString("render"));
  Antialiasing = set.value("Antialiasing", true).toBool();
  HighQualityAntialiasing = set.value("HighQualityAntialiasing", false).toBool();
  set.endGroup();
}

CircuitRenderArea::~CircuitRenderArea()
{

}

void CircuitRenderArea::setScale(double scale, int mx, int my){
  //_scale = scale < 0.75 ? 0.75 : scale;
  _scale = scale > 0.2 ? scale : 0.2;
  float y = float(p->verticalScrollBar()->sliderPosition()) / p->verticalScrollBar()->maximum();
  float x = float(p->horizontalScrollBar()->sliderPosition()) / p->horizontalScrollBar()->maximum();
  updateSize();
  p->verticalScrollBar()->setSliderPosition(t - (p->height() >> 1) + my);
  p->horizontalScrollBar()->setSliderPosition(l - (p->width() >> 1) + mx);
  update();
}

void CircuitRenderArea::paintEvent(QPaintEvent *){
  QPainter painter(this);
  //painter.scale(_scale,_scale);
  //painter.setPen(pen);
  //painter.setBrush(brush);

  if(Antialiasing) painter.setRenderHint(QPainter::Antialiasing);
  if(HighQualityAntialiasing) painter.setRenderHint(QPainter::HighQualityAntialiasing);

  painter.save();
  painter.translate(l,t);
  painter.drawLine(0,0,500*_scale,500*_scale);

  painter.restore();
  painter.drawLine(0,0,500*_scale,500*_scale);
  //std::cout << ++i << std::endl;
}
