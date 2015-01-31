#ifndef CIRCUITWIDGET_H
#define CIRCUITWIDGET_H

#include <QtWidgets>

#include "circuit.h"
#include "enum.h"

class CircuitScrollArea;

class CircuitWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CircuitWidget(Circuit * _circuit, QWidget *parent = 0);
  ~CircuitWidget();

  inline void scaleUp() { circuit->scaleUp(); }
  inline void scaleDown() { circuit->scaleDown(); }

  inline void saveFileAs(QString file) { circuit->saveFileAs(file); }
  inline void saveFile() { circuit->saveFile(); }
  inline bool hasPath() { return circuit->hasPath(); }
  inline bool isModyfied() { return circuit->isModyfied(); }
  inline bool isNew() { return circuit->newFile; }
  inline void destroyDrawingObject() { circuit->destroyDrawingObject(); }

  void updateTitle();
  void grabMouse();
  void releaseMouse();
  bool grabedMouse = false;
private:
  friend class Circuit;
  Circuit * circuit;

  void updateSize();
protected:
  void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
  void mouseMoveEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
  void mouseReleaseEvent( QMouseEvent * event ) Q_DECL_OVERRIDE;
  void mousePressEvent( QMouseEvent * event ) Q_DECL_OVERRIDE;
  void keyReleaseEvent ( QKeyEvent * event ) Q_DECL_OVERRIDE;
  ///void keyReleaseEvent ( QKeyEvent * event ) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // CIRCUITWIDGET_H
