#include "circuit.h"

#include "mainwindow.h"

#define selectedTool MainWindow::selectedTool
#define MAGICK_NUMBER 0x8a3f98c0

#ifdef CONSTEXPR
  constexpr float Circuit::scaleList[];
#else
  int Circuit::scaleListSize = SCALE_LIST_SIZE;
  float Circuit::scaleList[] = {SCALE_LIST};
#endif
Circuit::Circuit(QString path)
{
  if(!QFile::exists(path)) throw tr("File doesn't exist");
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
  if(objectVersion > OBJECT_VERSION) throw tr("File from newer version of KCircuit. Please upgrade KCircuit.");

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
        case K::Object::CAPACITOR:
          _objects.push_back(new CircuitCapacitor(in));
          break;
        case K::Object::COIL:
          _objects.push_back(new CircuitCoil(in));
          break;
        case K::Object::VDC:
          _objects.push_back(new CircuitVDC(in));
          break;
        case K::Object::ADC:
          _objects.push_back(new CircuitADC(in));
          break;
        case K::Object::DIODE:
          _objects.push_back(new CircuitDiode(in));
          break;
        case K::Object::GENERATOR:
          _objects.push_back(new CircuitGenerator(in));
          break;
        case K::Object::OPAMP:
          _objects.push_back(new CircuitOpAmp(in));
          break;
        default:
          qDebug() << "nieznany typ " << __FILE__ << " line " << __LINE__;
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
  _nowDrawing = nullptr;
  for( auto itr : _objects)
    {
      delete itr;
    }
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
  QPen pen(Qt::black);
  pen.setWidth(2);
  p.setPen(pen);
  for(auto itr : _objects)
    {
      itr->draw(p, _scale);
    }
  if(!s1){ _widget->centering(); s1 = true; }
}

void Circuit::exportToPNG(QString path)
{
  QImage pixmap(_width, _height, QImage::Format_ARGB32);
  pixmap.fill(Qt::white);
  QPainter p(&pixmap);
  QPen pen(Qt::black);
  pen.setWidth(2);
  p.setPen(pen);
  p.setRenderHint(QPainter::SmoothPixmapTransform);
  p.setRenderHint(QPainter::Antialiasing);

  for(auto itr : _objects)
    {
      itr->draw(p, 1);
    }
  QImage croped = pixmap.copy(this->getRectangle(pixmap));
  croped.save(path);
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

void Circuit::doubleClick()
{
  if(_nowDrawing)
    {
      auto status = _nowDrawing->doubleClick();
      if(status == K::DRAWED)
        {
          _nowDrawing = nullptr;
          _widget->releaseMouse();
          setModyfied();
        }
    }
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

void Circuit::rotate()
{
  if(_nowDrawing){
      rotation += 90; rotation %= 360;
      _nowDrawing->rotate();
      _widget->update();
    }
}

void Circuit::smallRotate()
{
  if(_nowDrawing && _nowDrawing->isSmallRotate()){
      rotation += 45; rotation %= 360;
      _nowDrawing->smallRotate();
      _widget->update();
    }
}

void Circuit::saveFile()
{
  QFile file(_path);
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);
  out << quint32(MAGICK_NUMBER);
  out << quint32(OBJECT_VERSION);

#if QT_VERSION >= 0x050400
  out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
#else
  out.setVersion(QDataStream::Qt_5_3);
#endif
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
  auto type = QFileInfo(newPath).completeSuffix();
  if(type != "qtc") newPath += ".qtc";
  _path = newPath;
  QFile file(_path);
  _name = QFileInfo(file).fileName();
  this->saveFile();
}

void Circuit::setModyfied(bool b) {modyfied = b; newFile = false; _widget->updateName();}

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
          _nowDrawing = new CircuitResistor(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::CAPACITOR:
          _nowDrawing = new CircuitCapacitor(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::COIL:
          _nowDrawing = new CircuitCoil(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::VDC:
          _nowDrawing = new CircuitVDC(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::ADC:
          _nowDrawing = new CircuitADC(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::DIODE:
          _nowDrawing = new CircuitDiode(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::GENERATOR:
          _nowDrawing = new CircuitGenerator(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::OPAMP:
          _nowDrawing = new CircuitOpAmp(Coordinate(event->x(),event->y()), _scale, rotation);
          break;
        case K::MOUSE:
        case K::WIRE:
          break;
        default:
          qDebug() << "selectedTool default in " << __FILE__ << " line " << __LINE__;
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
      if(!_widget->inVisibleRect(x,y) && selectedTool() != K::WIRE)
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

QRect Circuit::getRectangle(QImage &p)
{
  int r = 0;
  int l = p.width();
  int t = 0;
  int b = 0;

  bool e1 = true;
  for(int i = 0; i < p.height(); ++i)
    {
      bool e2 = true;
      for(int j = 0; j < p.width(); ++j)
        {
          if(QColor().fromRgb(p.pixel(j, i)) != Qt::white)
            {
              r = std::max(j, r);
              if(e2)
                {
                  l = std::min(j - 1, l);
                }
              e2 = false;
              e1 = false;
            }
        }
      if(e2 && e1)
        {
          t = i + 1;
        }
      if(!e2) b = i;
    }

  b = (b + MARGIN > p.height() ? p.height() : b + MARGIN);
  t = (t - MARGIN < 0 ? 0 : t - MARGIN);
  r = (r + MARGIN > p.width() ? p.width() : r + MARGIN);
  l = (l - MARGIN < 0 ? 0 : l - MARGIN);

  return QRect(l, t, r-l, b - t);
}

#undef selectedTool

