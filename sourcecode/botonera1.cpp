#include "botonera1.h"
void botonera1::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
estado = "Libre";
//pet = new std::queue<double>();
tiempo = INF;
}
double botonera1::ta(double t) {
//This function returns a double.
return tiempo;
}
void botonera1::dint(double t) {
printLog("\n BOTONERA delta int\n ");
if ((estado.compare("Libre")==0) ){
	std::stringstream v1;
	v1 << pet.size() ;
	char const *pchar = v1.str().c_str();
	printLog(" \n Queue size before of delete of an element: ");
	printLog(pchar);
	printLog(" \n");
	pet.pop(); //ver
	tiempo = INF;
	std::stringstream v2;
	v2 << pet.size() ;
	char const *pchar1 = v2.str().c_str();
	printLog(" \n Queue size after of insert of an element: ");
	printLog(pchar1);
	printLog(" \n");
}else{
	printLog("ERROR BOTONERA: delta int");
}
}
void botonera1::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
printLog("BOTONERA delta ext ");
double *aux;
aux = (double*) x.value;
std::string *aux2;
aux2 = static_cast<std::string*>(x.value);

printLog("\nEstado BOT: ");
printLog(estado.c_str());
printLog("\n");
if ((x.port == 0) && (estado.compare("Libre")==0)){
  std::stringstream v1;
	v1 << pet.size() ;
	char const *pchar = v1.str().c_str();
	printLog(" \n Queue size before of insert of an element: ");
	printLog(pchar);
	printLog(" \n");
    if (pet.size()<=0){
        pet.push(*aux);
	    tiempo = 0.0;
    }else{
        const long &result = pet.back();
        if (result!=*aux){
          pet.push(*aux);
	      tiempo = 0.0;  
	    }else{
            tiempo = INF;
        }
    }
	std::stringstream v2;
	v2 << pet.size() ;
	char const *pchar1 = v2.str().c_str();
	printLog(" \n Queue size after of insert of an element: ");
	printLog(pchar1);
	printLog(" \n");
}else{
	if ((x.port == 0) && (estado.compare("Ocupado")==0)) {
		std::stringstream v1;
		v1 << pet.size() ;
		char const *pchar = v1.str().c_str();
		printLog(" \n Queue size before of insert of an element: ");
		printLog(pchar);
		printLog(" \n");
		pet.push(*aux);
		tiempo = INF;
		std::stringstream v2;
		v2 << pet.size() ;
		char const *pchar1 = v2.str().c_str();
		printLog(" \n Queue size after of insert of an element: ");
		printLog(pchar1);
		printLog(" \n");
	}else{
		if ((x.port == 1) && (aux2->compare("Libre")==0)){
            estado = *aux2;            
            if (pet.size()>0){
				tiempo = 0.0;
            }else{
                printLog("Infinito");
                tiempo = INF;
            }
		}else{
			if ((x.port == 1) && (aux2->compare("Ocupado")==0)){
				estado = *aux2;
				tiempo = INF;
			}else{
				printLog("ERROR BOTONERA: delta ext");
			}
		}
	}
}
}
Event botonera1::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("SALIDA BOTONERA \n");
printLog("estado: ");
printLog(estado.c_str());
if ((estado.compare("Libre")==0) && (pet.size() != 0)){
	salida = pet.front();
}else{
	salida = 0;
	printLog("ERROR BOTONERA: salida");
}
;
std::stringstream v1;
	v1 << pet.size() ;
	char const *pchar = v1.str().c_str();
printLog(" \n");
	printLog(pchar);
printLog(" \n");
return Event(&salida,0);

/*	std::stringstream v;
	v << 1.0 * salida ;
	char const *pchar = v.str().c_str();
	printLog(pchar);
	printLog("   ");
*/
}
void botonera1::exit() {
//Code executed at the end of the simulation.

}
