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


class RightWidget;
class ListObjects;

class CircuitModel: public virtual CircuitData
{
public:
  CircuitModel(QString path);
  CircuitModel(CircuitSettings setings);
  virtual ~CircuitModel();

  QSize size();

  bool mouseMoved(QPoint p);
  void mouseDraged(QPoint d);

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
  void setRightWidget(RightWidget * r);

  void setCurrent(ObjectAbstract * o);

  ListObjects * listObjects;
  void setModyfied();

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
  bool rotate315();
  bool rotate270();


  void exportToPng(QString path);

  void paint(QPainter & p);
  void paintGrid(QPainter & p);

  void destroyDrawing();

  void release();

  bool press(QMouseEvent * e);

  void initPens();

  bool modyfied = false;

  void doubleClick();
private:
  std::list<ObjectAbstract *> objects;
  ObjectAbstract * drawing = nullptr;
  ObjectAbstract * current = nullptr;

  void newDrawing(QPoint p);
  void drawed();
  QPen stdPen;
  QPen drawingPen;
  QPen currentPen;

  QPoint p;

  quint32 ID;
  RightWidget * rightWidget;
  QRect getRectangle(QImage *p);
};

#endif // CIRCUITMODEL_H
