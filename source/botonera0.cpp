#include "botonera0.h"
void botonera0::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
estado = "Libre";
pet = new queue<double>();
tiempo = INF;
}
double botonera0::ta(double t) {
//This function returns a double.
return tiempo;
}
void botonera0::dint(double t) {
if  (pet.size() != 0){
	pet.pop(); //ver
	tiempo = INF;
}
}
void botonera0::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

	pet.push(x.value);
	tiempo = 0;
}
Event botonera0::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


	salida = pet.front();
return Event(&salida,0);
}
void botonera0::exit() {
//Code executed at the end of the simulation.

}
