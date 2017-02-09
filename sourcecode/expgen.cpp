#include "expgen.h"
void expgen::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

semilla = 0.5;
tiempo = 0;

p_e = 0.9;
//inicializar semilla del random
//ranGen = new CRandomMersenne(0);
srand (2);
}
double expgen::ta(double t) {
//This function returns a double.
return tiempo;
}
void expgen::dint(double t) {
//semilla = ranGen->CRandomMersenne::Random();
semilla = rand()* 1.00/ RAND_MAX ;
tiempo = (-1.0/p_e) * log(1.0-semilla);

/*printLog ("La semilla es "); 
std::stringstream val;
val << rand()* 1.00/ RAND_MAX ;
char const *pchar = val.str().c_str();
printLog(pchar);
*/

}
void expgen::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

}
Event expgen::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
if (semilla < 0.1){
	salida = 0;
}else{
	if (semilla < 0.2){
		salida = 1;
	}else{
		if (semilla < 0.3){
			salida = 2;
		}else{
			if (semilla < 0.4){
				salida = 3;
			}else{
				if (semilla < 0.5){
					salida = 4;
				}else{
					if (semilla < 0.6){
						salida = 5;
					}else{
						if (semilla < 0.7){
							salida = 6;
						}else{
							if (semilla < 0.8){
								salida = 7;
							}else{
								if (semilla < 0.9){
									salida = 8;
								}else{
									salida = 9;
								}
							}
						}
					}
				}
			}
		}
	}
}
printLog("\nSALIDA DEL GENERADOR\n");
std::stringstream v;
	v << salida ;
	char const *pchar = v.str().c_str();
	printLog(pchar);
printLog("\n");
return Event(&salida, 0);
}
void expgen::exit() {
//Code executed at the end of the simulation.

}
