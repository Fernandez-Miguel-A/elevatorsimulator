//CPP:sourcecode/expgen.cpp
#if !defined expgen_h
#define expgen_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "sstream"
#include "string"
#include "math.h"
#include "stdlib.h"
#include "randomc.h"
#include "stocc.h"
#include "/home/leo/powerdevs/engine/pdevslib.h"


class expgen: public Simulator { 
// Declare the state,
// output variables
// and parameters

// Estado
double semilla;
double tiempo;

// Variables auxiliares
double p_e;
double salida;
//CRandomMersenne *ranGen;

public:
	expgen(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
