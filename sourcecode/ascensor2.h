//CPP:proyecto/ascensor2.cpp
#if !defined ascensor2_h
#define ascensor2_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "sstream"
#include "string"
#include "math.h"
#include "stdlib.h"


class ascensor2: public Simulator { 
// Declare the state,
// output variables
// and parameters


// Estado
double piso_actual;
double tiempo;
std::string accion;

// Variables Auxiliares
double altura_piso;
double velocidad;

// Variables Salida
double y;

#define INF 1e20
public:
	ascensor2(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
