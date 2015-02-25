#ifndef TEXTPAINTER_H
#define TEXTPAINTER_H

#include <QString>
#include <QPainter>
#include <QImage>

#include "global.h"


class TextPainter
{
public:
  TextPainter(QString ktext, float s);
  ~TextPainter();
  QImage * getCropedImage();
private:
  QImage * img;
  QRect getRectangle(QImage *p);
};

#endif // TEXTPAINTER_H
