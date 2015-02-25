#include "textpainter.h"

#include <QTextDocument>

TextPainter::TextPainter(QString t, float s)
{
  img = new QImage(300*s, 50*s, QImage::Format_ARGB32_Premultiplied);
  img->fill(Qt::transparent);

  t.replace(QRegExp("_([^{])"), "<sub>\\1</sub>");
  t.replace(QRegExp("_\\{([^}]*)\\}"), "<sub>\\1</sub>");

  t.replace(QRegExp("\\^([^{])"), "<sup>\\1</sup>");
  t.replace(QRegExp("\\^\\{([^}]*)\\}"), "<sup>\\1</sup>");
  t.replace(QRegExp("\\\\(Omega|ohm|Ohm)"), "Ω");

  QPainter *p = new QPainter(img);
  p->scale(s,s);
  QTextDocument doc;
  doc.setHtml("<p style=\" font-size: 30px; \">" + t + "</font>");
  doc.drawContents(p);
  delete p;
}

TextPainter::~TextPainter()
{
  delete img;
}

QImage *TextPainter::getCropedImage()
{
  return new QImage(img->copy(getRectangle(img)));
}

QRect TextPainter::getRectangle(QImage * p)
{
  int r = 0;
  int l = p->width();
  int t = 0;
  int b = 0;
  bool e1 = true;
  for(int i = 0; i < p->height(); ++i)
    {
      bool e2 = true;
      for(int j = 0; j < p->width(); ++j)
        {
          if(QColor().fromRgba(p->pixel(j, i)) != Qt::transparent)
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
int MARGIN = 5;
  b = (b + MARGIN > p->height() ? p->height() : b + MARGIN);
  t = (t - MARGIN < 0 ? 0 : t - MARGIN);
  r = (r + MARGIN > p->width() ? p->width() : r + MARGIN);
  l = (l - MARGIN < 0 ? 0 : l - MARGIN);

  return QRect(l, t, r-l, b - t);
}
