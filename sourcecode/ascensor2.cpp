#include "ascensor2.h"
void ascensor2::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

piso_actual = 0.0;
tiempo = INF;
accion = "Parar";

altura_piso = 2.0;
velocidad = 1.0;

}
double ascensor2::ta(double t) {
//This function returns a double.
std::stringstream v1;
	v1 << tiempo ;
	char const *pchar = v1.str().c_str();
	printLog(" Tiempo ascensor ");
	printLog(pchar);
printLog(" ");
return tiempo;
}
void ascensor2::dint(double t) {
printLog("ASCENSOR delta int ");
if (accion.compare("Parar")==0){
	tiempo = INF;
}else{
	if (accion.compare("Arriba")==0){
		piso_actual++;
		tiempo = 1.0 * altura_piso/velocidad;
	}else{
		if (accion.compare("Abajo")==0){
			piso_actual--;
			tiempo = 1.0 * altura_piso/velocidad;
		}else{
			printLog("ERROR ASCENSOR: delta interna ");
			/*piso_actual = 0.0;
			tiempo = INF;
			accion = "Parar";
			*/
		}
	}
}
}
void ascensor2::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
printLog("ASCENSOR delta ext ");
std::string *aux;
aux = static_cast<std::string*>(x.value);
if ((accion.compare("Parar")==0) &&
	 (aux->compare("Parar")==0)){
	tiempo = INF;
	accion = *aux;
}else{
	if ((accion.compare("Parar")==0) &&
		 (aux->compare("Arriba")==0)){
		//piso_actual++;
		tiempo = 0.0;	
		accion = *aux;
	}else{
		if ((accion.compare("Parar")==0) &&
			 (aux->compare("Abajo")==0)){
			//piso_actual--;
			tiempo = 0.0;
			accion = *aux;
		}else{
			if (((accion.compare("Abajo")==0) || (accion.compare("Arriba")==0)) && 
				((aux->compare("Abajo")==0) || (aux->compare("Arriba")==0))){
				tiempo = 1.0 * tiempo - e;
			}else{
				if ((accion.compare("Abajo")==0) && 
					 (aux->compare("Parar")==0)){
					piso_actual++;
					tiempo = INF;
					accion = *aux;
				}else{
					if ( (accion.compare("Arriba")==0) && (aux->compare("Parar")==0)){
						piso_actual--;
						tiempo = INF;
						accion = *aux;
					}else{
						printLog("ERROR ASCENSOR: delta ext ");
					}
				}
			}
		}	
	}
}

}
Event ascensor2::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("SALIDA ASCENSOR \n");
y = piso_actual;
std::stringstream v1;
	v1 << piso_actual ;
	char const *pchar = v1.str().c_str();
	printLog(" Piso actual ");
	printLog(pchar);
printLog(" ");

return Event(&y,0);
}
void ascensor2::exit() {
//Code executed at the end of the simulation.

}
