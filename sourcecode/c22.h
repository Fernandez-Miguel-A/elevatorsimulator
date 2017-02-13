//CPP:proyecto/c22.cpp
#if !defined c22_h
#define c22_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "sstream"
#include "string"
#include "math.h"
#include "stdlib.h"


class c22: public Simulator { 
// Declare the state,
// output variables
// and parameters
// Estado ascensor 1
double piso1;
double destino1;
std::string e1;
double tiempo1;
double demora1;
double ult_dest1;
std::queue<double> cola1;

//Estado ascensor 2
double piso2;
double destino2;
std::string e2;
double tiempo2;
double demora2;
double ult_dest2;

int counter_aux;

std::queue<double> cola2;

double puerto_salida;

std::string salida;

#define INF 1e20;

public:
	c22(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
private:
	double minimo(double, double);
	bool disponibilidad();
	double optimo();
};
#endif
