#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QString>

#include <vector>

#include "circuitwire.h"
#include "enum.h"

class CircuitWidget;

class Circuit
{
  friend class CircuitWidget;
public:
  Circuit(QString name);
  ~Circuit();

  inline void setWidget(CircuitWidget * widget) { _widget = widget; }

  inline QString name(){return _name;}

  void draw(QPainter&);
  void mouseEvent(QMouseEvent * event);
  void keyPressEvent(QKeyEvent * event);

  inline double scale() { return _scale; }

  inline int width() { return _width; }
  inline void setWidth(int width) { _width = width; }
  inline int height() { return _height; }
  inline void setHeight(int height) { _height = height; }

  void scaleUp();
  void scaleDown();
  void setScale(double scale);

  static bool showGrid;

private:
  ///TMP NAME
  QString _name;
  CircuitWidget * _widget;

  std::vector<AbstractCircuitObject*> _objects;
  AbstractCircuitObject * _nowDrawing = nullptr;

  void drawing(QMouseEvent *event);

  constexpr static int scaleListSize = 9;
  constexpr static double scaleList[scaleListSize] = {.5, .66, .8, 1, 1.33, 1.66, 2, 2.5, 3};
  double _scale = 1;

  int _width = 1200;
  int _height = 800;
};

#endif // CIRCUIT_H
