//CPP:proyecto/controlador1.cpp
#if !defined controlador1_h
#define controlador1_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "sstream"
#include "string"
#include "math.h"
#include "stdlib.h"


class controlador1: public Simulator { 
// Declare the state,
// output variables
// and parameters

// Estado
double piso;
double destino;
double tiempo;
std::string estado;
double puerto_salida;

// Variables Salida
std::string salida;


#define INF 1e20
public:
	controlador1(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
