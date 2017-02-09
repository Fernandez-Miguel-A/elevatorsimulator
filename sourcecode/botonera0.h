//CPP:proyecto/botonera0.cpp
#if !defined botonera0_h
#define botonera0_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "string"


class botonera0: public Simulator { 
// Declare the state,
// output variables
// and parameters

// Estado
std::string estado;	
std::queue<double> pet;
double tiempo;

// Variables de Salida
double salida;

#define INF 1e20
public:
	botonera0(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
