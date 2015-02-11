#ifndef ENUM_H
#define ENUM_H

#include <QDataStream>
#include <QtWidgets>

#define VERSION "0.0.0"

#ifdef __GNUC__
#ifndef __clang__
  #define CONSTEXPR
  #define MATH_CONSTEXPR
#else
  #define CONSTEXPR
#endif
#elif defined(_MSC_VER)
#endif

#ifndef MATH_CONSTEXPR
  #define sqrt2 1.4142135623730951
#endif

class MainWidget;
class AbstractCircuitObject;

namespace K
{
  enum tool{MOUSE, WIRE, RESISTOR, CAPACITOR, COIL, VDC, ADC, DIODE, GENERATOR, OPAMP};
  enum status{DRAWING, DRAWED, DESTROY};

  namespace Object
  {
    enum object:quint8{WIRE = 1, RESISTOR = 2, CAPACITOR = 3, COIL = 4, VDC = 5, ADC = 6, DIODE = 7, GENERATOR = 8, OPAMP = 9};
  }

  struct info {
    K::Object::object type;
    QString name;
    AbstractCircuitObject * ptr;
  };
}
#endif // ENUM_H

