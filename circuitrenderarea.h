#ifndef CIRCUITRENDERAREA_H
#define CIRCUITRENDERAREA_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

#include <iostream>

#include <stdio.h>

class CircuitRenderArea : public QWidget
{
  Q_OBJECT
public:
  explicit CircuitRenderArea(QScrollArea *parent);
  ~CircuitRenderArea();
  void setScale(double scale, int mx, int my);
  inline double scale(){return _scale;}

  int width();
  int height();

  void updateSize();

signals:

public slots:

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  //void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
  QPen pen;
  QBrush brush;
  QScrollArea * p;

  void loadRenderHint();
  bool Antialiasing;
  bool HighQualityAntialiasing;

  void updateLRTB();
  uint32_t l,r,t,b;

  int i;

  double _scale;
};

#endif // CIRCUITRENDERAREA_H
