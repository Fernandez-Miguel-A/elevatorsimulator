#include "controlador1.h"
void controlador1::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
piso = 0.0;
destino = 0.0;
tiempo = INF;
estado = "Libre";
puerto_salida = 0;


/*	std::stringstream v;
	v << 1.0 * salida ;
	char const *pchar = v.str().c_str();
	printLog(pchar);
	printLog("   ");
*/
}
double controlador1::ta(double t) {
//This function returns a double.
return tiempo;
}
void controlador1::dint(double t) {
printLog("CONTROLADOR delta int ");
if ((puerto_salida == 0) && 
(estado.compare("Ocupado")==0) && 
(piso == destino)){
	tiempo = 0.0;
	estado = "Libre";
	puerto_salida = 1;
//printLog("A1 ");
}else{
	if ((puerto_salida == 0) && 
	(estado.compare("Ocupado")==0) && 
	(piso != destino)){
		tiempo = 0.0;
		puerto_salida = 1;
//printLog("A2 ");
	}else{
		if (puerto_salida == 1){
			tiempo = INF;
			puerto_salida = 0;
//printLog("A3 ");
		}else{
			printLog("ERROR CONTROLADOR: delta int");
		}
	}
}
}
void controlador1::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
printLog("CONTROLADOR delta ext ");
double *aux;
aux = (double*) x.value;
if ((estado.compare("Libre")==0) && (x.port == 0)){
	destino = *aux;
   std::stringstream v;
	v << destino ;
	char const *pchar = v.str().c_str();
	printLog("Destino ");
	printLog(pchar);
printLog(" s");
	
	tiempo = 0.0;
	estado = "Ocupado";
//	printLog("1 ");	
}else{
	if ((estado.compare("Ocupado")==0) && (x.port == 1) &&
		 (*aux == destino)){
		piso = *aux;
		tiempo = 0.0;
		puerto_salida = 0;
//printLog("2 ");
	}else{
		if ((estado.compare("Ocupado")==0) && (x.port == 1) &&
			 (*aux != destino)){
		piso = *aux;
		tiempo = INF;
		puerto_salida = 0;
//printLog("3 ");
		}else{
			printLog("ERROR CONTROLADOR: delta ext ");
		}
	}
}
}
Event controlador1::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("SALIDA CONTROLADOR \n");
if (puerto_salida == 0 && piso == destino){
	salida = "Parar";
   printLog("Salida de controlador a ascensor: Parar ");
}else{
	if (puerto_salida == 0 && piso > destino){
		salida = "Abajo";
     printLog("Salida de controlador a ascensor: Abajo ");
	}else{
		if (puerto_salida == 0 && piso < destino){
			salida = "Arriba";
			printLog("Salida de controlador a ascensor: Arriba ");
		}else{
			if (puerto_salida == 1){
				salida = estado;
				printLog("Salida de controlador a botonera:");
				printLog(estado.c_str());
//printLog("B4 ");
			}else{
				printLog("ERROR CONTROLADOR: salida ");
			}
		}
	}
}
return Event(&salida,puerto_salida);
}
void controlador1::exit() {
//Code executed at the end of the simulation.

}
