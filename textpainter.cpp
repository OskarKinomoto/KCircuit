#include "textpainter.h"

#include <QTextDocument>

TextPainter::TextPainter(QString t, float s)
{
  img = new QImage(300*s, 50*s, QImage::Format_ARGB32_Premultiplied);
  img->fill(Qt::transparent);

  t.replace(QRegExp("\\^([^{])"), "<sup>\\1</sup>");
  t.replace(QRegExp("\\^\\{([^}]*)\\}"), "<sup>\\1</sup>");
  t.replace(QRegExp("\\\\(Omega|ohm|Ohm)"), "Ω");
  t.replace(QRegExp("\\\\(omega)"), "ω");
  t.replace(QRegExp("\\\\(alpha)"), "α");
  t.replace(QRegExp("\\\\(Αlpha)"), "Α");
  t.replace(QRegExp("\\\\(beta)"), "β");
  t.replace(QRegExp("\\\\(Beta)"), "Β");
  t.replace(QRegExp("\\\\(gamma)"), "γ");
  t.replace(QRegExp("\\\\(Gamma)"), "Γ");
  t.replace(QRegExp("\\\\(delta)"), "δ");
  t.replace(QRegExp("\\\\(Delta)"), "Δ");
  t.replace(QRegExp("\\\\(epsilon)"), "ε");
  t.replace(QRegExp("\\\\(Epsilon)"), "Ε");
  t.replace(QRegExp("\\\\(rho)"), "ρ");
  t.replace(QRegExp("\\\\(Rho)"), "Ρ");
  t.replace(QRegExp("\\\\(tau)"), "τ");
  t.replace(QRegExp("\\\\(Tau)"), "Τ");
  t.replace(QRegExp("\\\\(tetha)"), "θ");
  t.replace(QRegExp("\\\\(Tetha)"), "Θ");
  t.replace(QRegExp("\\\\(jota)"), "ι");
  t.replace(QRegExp("\\\\(Jota)"), "Ι");
  t.replace(QRegExp("\\\\(pi)"), "π");
  t.replace(QRegExp("\\\\(Pi)"), "Π");
  t.replace(QRegExp("\\\\(sigma)"), "σ");
  t.replace(QRegExp("\\\\(Sigma)"), "Σ");
  t.replace(QRegExp("\\\\(phi)"), "φ");
  t.replace(QRegExp("\\\\(Phi)"), "Φ");
  t.replace(QRegExp("\\\\(etha)"), "η");
  t.replace(QRegExp("\\\\(Etha)"), "Η");
  t.replace(QRegExp("\\\\(xi)"), "ξ");
  t.replace(QRegExp("\\\\(Xi)"), "Ξ");
  t.replace(QRegExp("\\\\(kappa)"), "κ");
  t.replace(QRegExp("\\\\(Kappa)"), "Κ");
  t.replace(QRegExp("\\\\(lambda)"), "λ");
  t.replace(QRegExp("\\\\(Lambda)"), "Λ");
  t.replace(QRegExp("\\\\(zeta)"), "ζ");
  t.replace(QRegExp("\\\\(Zeta)"), "Ζ");
  t.replace(QRegExp("\\\\(chi)"), "χ");
  t.replace(QRegExp("\\\\(Chi)"), "Χ");
  t.replace(QRegExp("\\\\(psi)"), "ψ");
  t.replace(QRegExp("\\\\(Psi)"), "Ψ");
  t.replace(QRegExp("\\\\(nu)"), "ν");
  t.replace(QRegExp("\\\\(Nu)"), "Ν");
  t.replace(QRegExp("\\\\(mu)"), "μ");
  t.replace(QRegExp("\\\\(Mu)"), "Μ");

  t.replace(QRegExp("_([^{])"), "<sub>\\1</sub>");
  t.replace(QRegExp("_\\{([^}]*)\\}"), "<sub>\\1</sub>");

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
