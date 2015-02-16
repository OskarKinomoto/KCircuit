#ifndef CIRCUITMODEL_H
#define CIRCUITMODEL_H

#include <QString>
#include <QSize>
#include <QPainter>
#include <list>

#include "circuitsettings.h"
#include "circuitdata.h"
#include "objects.h"
#include "tools.h"

#include "history.h"
#include <QMouseEvent>

class ListObjects;

class CircuitModel: public virtual CircuitData
{
public:
  CircuitModel(QString path);
  CircuitModel(CircuitSettings setings);
  virtual ~CircuitModel();

  QSize size();

  bool mouseMoved(QPoint p);

  void updateTitle();

  void addObject(ObjectAbstract * o);
  void removeObject(ObjectAbstract * o, bool history = false);
  void removeCurrent();

  void saveAs(QString path);
  void save();

  bool hasPath();

  bool isModyfied();

  std::list<ObjectAbstract *>& list();
  inline bool isDrawing(ObjectAbstract * d) { return d == drawing; }

  void setList(ListObjects* l);

protected:
  QString path;
  QString name;
  History * history;

  int widthG;
  int heightG;

  float scale = 1;

  quint16 angle = 0;

  void scaleUp();
  void scaleDown();

  bool rotate45();
  bool rotate90();

  void paint(QPainter & p);
  void paintGrid(QPainter & p);

  void destroyDrawing();

  bool release();

  bool press(QMouseEvent * e);

  void initPens();

  bool modyfied = false;
  void setModyfied();

private:
  std::list<ObjectAbstract *> objects;
  ObjectAbstract * drawing = nullptr;
  ObjectAbstract * current = nullptr;

  void newDrawing(QPoint p);
  void drawed();
  QPen stdPen;
  QPen drawingPen;
  QPen currentPen;

  quint32 ID = 0;

  ListObjects * listObjects;
};

#endif // CIRCUITMODEL_H
