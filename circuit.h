#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QObject>

#include <QString>
#include <QFile>
#include <QDataStream>

#include <QDebug>

#include <list>
#include <algorithm>

#include "circuitwire.h"
#include "circuitresistor.h"
#include "circuitcapacitor.h"
#include "circuitcoil.h"
#include "circuitvdc.h"
#include "circuitadc.h"
#include "circuitdiode.h"
#include "circuitgenerator.h"
#include "circuitopamp.h"

#include "include.h"

#define MARGIN 30

class CircuitWidget;

class Circuit : public QObject
{
  Q_OBJECT

  friend class CircuitWidget;
public:
  Circuit(QString path);
  Circuit();
  ~Circuit();

  inline void setWidget(CircuitWidget * widget) { _widget = widget; }

  inline QString name(){QString tmp; if(modyfied) tmp += "*"; tmp+=_name; return tmp;}

  void draw(QPainter&);
  void exportToPNG(QString path);
  void mouseEvent(QMouseEvent * event);
  void doubleClick();

  inline double scale() { return _scale; }

  inline int width() { return _width; }
  inline void setWidth(int width) { _width = width; }
  inline int height() { return _height; }
  inline void setHeight(int height) { _height = height; }

  void scaleUp();
  void scaleDown();
  void setScale(double scale);
  void rotate();
  void smallRotate();

  static bool showGrid;

  void saveFile();
  void saveFileAs(QString newPath);
  inline bool hasPath() { return _path != ""; }
  inline bool isModyfied() { return modyfied; }
  inline void setModyfied(bool b = true);

  inline void resetRotation() {rotation = 0;}

  void destroyDrawingObject();

  bool newFile = false;

   std::list<AbstractCircuitObject*>* lista() { return &_objects; }

private:
  QString _name;
  QString _path;
  quint32 num = 0;

  bool modyfied = false;
  quint16 rotation = 0;

  CircuitWidget * _widget;

  std::list<AbstractCircuitObject*> _objects;
  AbstractCircuitObject * _nowDrawing = nullptr;

  void drawing(QMouseEvent *event);

  void updateInfoBox();


#define SCALE_LIST_SIZE 9
#define SCALE_LIST .5, .66, .8, 1, 1.33, 1.66, 2, 2.5, 3
#ifdef CONSTEXPR
  constexpr static int scaleListSize = SCALE_LIST_SIZE;
  constexpr static float scaleList[scaleListSize] = {SCALE_LIST};
#else
  static int scaleListSize;
  static float scaleList[];
#endif


  double _scale = 1;
  int _width = 1200;
  int _height = 800;

  QRect getRectangle(QImage & p);

  bool s1 = false;
};

#endif // CIRCUIT_H
