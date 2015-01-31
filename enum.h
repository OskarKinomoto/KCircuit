#ifndef ENUM_H
#define ENUM_H

#include <QDataStream>

namespace K
{
  enum tool{MOUSE, WIRE, RESISTOR};
  enum status{DRAWING, DRAWED, DESTROY};

  namespace Object
  {
    enum object:quint8{WIRE = 1, RESISTOR = 2};
  }
}


#endif // ENUM_H

