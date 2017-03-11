//CPP:proyecto/botonera1.cpp
#if !defined botonera1_h
#define botonera1_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "sstream"
#include "string"
#include "math.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
using namespace std;

class botonera1: public Simulator { 
// Declare the state,
// output variables
// and parameters

// Estado
std::string estado;
std::queue<double> pet;
double tiempo;

// Variables de Salida
double salida;
// File
ofstream myfile;

#define INF 1e20
public:
	botonera1(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
