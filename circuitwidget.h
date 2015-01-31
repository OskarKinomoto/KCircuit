#ifndef CIRCUITWIDGET_H
#define CIRCUITWIDGET_H

#include <QtWidgets>

#include "circuit.h"
#include "enum.h"

class CircuitWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CircuitWidget(Circuit * _circuit, QWidget *parent = 0);
  ~CircuitWidget();

  inline void scaleUp() { circuit->scaleUp(); }
  inline void scaleDown() { circuit->scaleDown(); }

private:
  friend class Circuit;
  Circuit * circuit;

  void updateSize();

protected:
  void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
  void mouseMoveEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
  void mouseReleaseEvent( QMouseEvent * event ) Q_DECL_OVERRIDE;
  void mousePressEvent( QMouseEvent * event ) Q_DECL_OVERRIDE;
  void keyPressEvent ( QKeyEvent * event ) Q_DECL_OVERRIDE;
  ///void keyReleaseEvent ( QKeyEvent * event ) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // CIRCUITWIDGET_H
