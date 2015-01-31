#include "circuit.h"

#include "mainwindow.h"

#define selectedTool MainWindow::selectedTool
#define MAGICK_NUMBER 0x8a3f98c0

constexpr double Circuit::scaleList[];

Circuit::Circuit(QString path)
{
  if(!QFile::exists(path)) throw tr("File don't exist");
  _path = path;

  QFile file(path);
  _name = QFileInfo(file).fileName();
  file.open(QIODevice::ReadOnly);
  QDataStream in(&file);

  quint32 magick;
  in >> magick;
  if(magick != MAGICK_NUMBER) throw tr("Wrong type or corupt file");

  quint32 objectVersion;
  in >> objectVersion;
  if(objectVersion > OBJECT_VERSION) throw tr("File newer than program. Please upgrade QtCircuit.");

  quint32 count;
  in >> count;
  _objects.reserve(count);

  for(quint32 i = 0; i < count; ++i)
    {
      quint32 io;
      in >> io;

      switch(io)
        {
        case K::Object::WIRE:
          _objects.push_back(new CircuitWire(in));
          break;
        case K::Object::RESISTOR:
          _objects.push_back(new CircuitResistor(in));
          break;
        default:
          qDebug() << "nieznany typ :<";
          break;
        }
    }
}

Circuit::Circuit()
{
  _name = tr("new");
  _path = "";
  newFile = true;
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

void Circuit::keyReleaseEvent(QKeyEvent *event)
{
  if(_nowDrawing != nullptr)
    {
      auto status = _nowDrawing->keyEvent(event, _scale);
      if(status == K::DRAWED)
        {
          _nowDrawing = nullptr;
          _widget->releaseMouse();
          setModyfied();
        }
      if(status == K::DESTROY)
        this->destroyDrawingObject();
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
  if(scale > scaleList[0] && scale < scaleList[scaleListSize - 1])
    {
      _scale = scale;
      _widget->updateSize();
    }
}

void Circuit::saveFile()
{
  QFile file(_path);
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);
  out << quint32(MAGICK_NUMBER);
  out << quint32(OBJECT_VERSION);

  out.setVersion(QDataStream::Qt_5_4);

  quint32 count = 0;
  out << count;

  for(auto object : _objects)
    {
      if(object->save(out)) ++count;
    }
  out.device()->seek(8);
  out << count;

  setModyfied(false);
}

void Circuit::saveFileAs(QString newPath)
{
  _path = newPath;
  this->saveFile();
}

void Circuit::destroyDrawingObject()
{
  if(_nowDrawing != nullptr)
    {
      delete _nowDrawing;
      _nowDrawing = nullptr;
      _objects.pop_back();
      _widget->releaseMouse();
    }
}

void Circuit::drawing(QMouseEvent * event)
{
  if(_nowDrawing == nullptr && event->button() == Qt::LeftButton && selectedTool() == K::WIRE)
    {
      _nowDrawing = new CircuitWire(Coordinate(event->x(),event->y()), _scale);
      _objects.push_back(_nowDrawing);
      _widget->grabMouse();
    }
  else if(_nowDrawing == nullptr)
    {
      switch(selectedTool())
        {
        case K::RESISTOR:
          _nowDrawing = new CircuitResistor(Coordinate(event->x(),event->y()), _scale);
          break;
        case K::MOUSE:
        case K::WIRE:
          break;
        default:
          qDebug() << "selectedTool default in " << __FILE__;
          break;
        }
      if(_nowDrawing)
        {
          _objects.push_back(_nowDrawing);
          _widget->grabMouse();
        }
    }
  else
    {
      int x = event->x();
      int y = event->y();
      if((x < 0 || y < 0 || y > _widget->height() || x > _widget->width()) && selectedTool() != K::WIRE)
        {
          //Out of bonds
          this->destroyDrawingObject();
        }
      else
        {
          auto status = _nowDrawing->mouseEvent(event, _scale);
          if(status == K::DRAWED)
            {
              _nowDrawing = nullptr;
              _widget->releaseMouse();
              setModyfied();
            }
          if(status == K::DESTROY)
            this->destroyDrawingObject();
        }
    }

  _widget->update();
}

#undef selectedTool

