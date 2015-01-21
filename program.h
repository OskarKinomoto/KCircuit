#ifndef PROGRAM_H
#define PROGRAM_H

#include "qtcircuitmain.h"
#include "circuitwidget.h"
//#include "circuit.h"

#include <list>
#include <thread>

class QtCircuitMain;

class Program
{

private:
  QtCircuitMain * window;
  //std::list<Circuit*> circs;
  bool pModified;

public:
  Program(QtCircuitMain *);
  ~Program();

  int save(int circ_no);

  inline bool modified(){return pModified;}
  inline void set_modified(bool a){pModified = a;}

};

#endif // PROGRAM_H
