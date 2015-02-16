#ifndef GLOBAL_H
#define GLOBAL_H

/// grep "*" tmp | sed -e 's/[\t ]*[a-zA-Z]* \* /delete /g' -e 's/\/\/[a-zA-Z ]*//g'
#include <QtGlobal>

//externy~
#include <QDebug>
#include <QStandardPaths>

class QFont;
class QIcon;
class TabWidget;

namespace K
{
#ifdef Q_OS_WINDOWS
  const quint32 magicknumber = 0x5F6B7463;
  const quint16 objectversion = 0;
#else
  constexpr quint32 magicknumber = 0x5F6B7463;
  constexpr quint16 objectversion = 0;
#endif
  extern QString home;
  extern QFont oxygen;
  extern bool breeze;
  extern int grid;
  extern bool showGrid;
  extern float gs;

  extern QIcon pointerI;
  extern QIcon resistorI;

  extern TabWidget * tabWidget;

  const float sqrt2 = 1.414213;

  namespace degrees
  {
    enum degree{D0 = 0, D45, D90, D135, D180, D225, D270, D315, degreeSize};
    extern double sine[];
    extern double cosine[];
    degree angle2enum(int angle);
  }
}

#endif // GLOBAL_H

