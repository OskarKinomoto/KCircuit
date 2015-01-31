#include "circuit.h"

#include "mainwindow.h"
#define selectedTool MainWindow::selectedTool

constexpr double Circuit::scaleList[];

Circuit::Circuit(QString name)
{
  _name = name;
}

Circuit::~Circuit()
{

}

void Circuit::draw(QPainter &p)
{
  //Draw grid :)
  if(showGrid)
    {
      p.save();
      QPen pen(Qt::darkGreen);
      //if(scale > 1.5)
      //pen.setWidthF(_scale);
      p.setPen(pen);
      float gs = grid*_scale;
      int w = _widget->width();
      int h = _widget->height();
      for(float i = 0; i < w; i += gs)
        for(float j = 0; j < h; j += gs)
          p.drawPoint(i, j);
      p.restore();
    }

  for(auto itr : _objects)
    {
      itr->draw(p, _scale);
    }
}

void Circuit::mouseEvent(QMouseEvent *event)
{
  switch(selectedTool())
    {
      case K::MOUSE:
      ///TODO ergo znajdywanie co gdzie i jak :)
      break;

    default:
      this->drawing(event);
      break;
    }
}

void Circuit::keyPressEvent(QKeyEvent *event)
{
  if(_nowDrawing != nullptr)
    {
      auto status = _nowDrawing->keyEvent(event, _scale);
      if(status == K::DRAWED)
        {
          _nowDrawing = nullptr;
          _widget->releaseMouse();
        }
      if(status == K::DESTROY)
        {
          delete _nowDrawing;
          _nowDrawing = nullptr;
          _objects.pop_back();
          _widget->releaseMouse();
        }
    }
  _widget->update();
}

void Circuit::scaleUp()
{
  for(int i = 0; i < scaleListSize; ++i)
    {
      if(_scale < scaleList[i])
        {
          _scale = scaleList[i];
          _widget->updateSize();
          return;
        }
    }
}

void Circuit::scaleDown()
{
  for(int i = scaleListSize - 1; i > -1; --i)
    {
      if(_scale > scaleList[i])
        {
          _scale = scaleList[i];
          _widget->updateSize();
          return;
        }
    }
}

void Circuit::setScale(double scale)
{

}

void Circuit::drawing(QMouseEvent * event)
{
  if(_nowDrawing == nullptr && event->button() == Qt::LeftButton && selectedTool() == K::WIRE)
    {
      _nowDrawing = new CircuitWire(Coordinate(event->x(),event->y()), _scale);
      _objects.push_back(_nowDrawing);
      /// COS TU ZMIENIC :)
      _widget->grabMouse();
    }
  else if(_nowDrawing == nullptr)
    {
      ///switch na resistory
    }
  else
    {
      auto status = _nowDrawing->mouseEvent(event, _scale);
      if(status == K::DRAWED)
        {
          _nowDrawing = nullptr;
          _widget->releaseMouse();
        }
      if(status == K::DESTROY)
        {
          delete _nowDrawing;
          _nowDrawing = nullptr;
          _objects.pop_back();
          _widget->releaseMouse();
        }
    }

  _widget->update();
}

#undef selectedTool

