#ifndef CIRCUITSETTINGS_H
#define CIRCUITSETTINGS_H

struct CircuitSettings {
  int widthG;
  int heightG;
  static CircuitSettings base() { return {200, 100}; }
};

#endif // CIRCUITSETTINGS_H
