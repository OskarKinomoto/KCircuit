#ifndef ENUM_H
#define ENUM_H

#include <QDataStream>

namespace K
{
  enum tool{MOUSE, WIRE, RESISTOR, CAPACITOR};
  enum status{DRAWING, DRAWED, DESTROY};

  namespace Object
  {
    enum object:quint8{WIRE = 1, RESISTOR = 2, CAPACITOR = 3};
  }
}


#endif // ENUM_H

