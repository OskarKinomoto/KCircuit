#ifndef ENUM_H
#define ENUM_H

#include <QDataStream>
#include <QtWidgets>

class MainWidget;

namespace K
{
  enum tool{MOUSE, WIRE, RESISTOR, CAPACITOR, COIL, VDC, ADC, DIODE, GENERATOR, OPAMP};
  enum status{DRAWING, DRAWED, DESTROY};

  namespace Object
  {
    enum object:quint8{WIRE = 1, RESISTOR = 2, CAPACITOR = 3, COIL = 4, VDC = 5, ADC = 6, DIODE = 7, GENERATOR = 8, OPAMP = 9};
  }
}


#endif // ENUM_H

