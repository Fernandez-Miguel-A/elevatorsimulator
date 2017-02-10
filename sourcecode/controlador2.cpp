#include "controlador2.h"
double controlador2::minimo(double val1, double val2){
if (val1 <= val2){
	return val1;
}else{
	return val2;
}
}
bool controlador2::disponibilidad(){
	return (e1.compare("Libre") == 0 || e2.compare("Libre") == 0);
}
double controlador2::optimo(double t){
    if (counter_aux%2==0){
        return 1;
    }else{
        return 2;
    }
    return 2;
    if (e1.compare("Libre") == 0){
		return 1;
	}else{
		if (e2.compare("Libre") == 0){
			return 2;
		}else{	
			return 0;
		}	
	}
}
void controlador2::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
piso1 = 0;
destino1 = 0;
e1 = "Libre";
tiempo1 = INF;
demora1 = 0;
ult_dest1 = 0;

piso2 = 0;
destino2 = 0;
e2 = "Libre";
tiempo2 = INF;
demora2 = 0;
ult_dest2 = 0;

counter_aux = 0;
puerto_salida = 0;
}
double controlador2::ta(double t) {
//This function returns a double.
printLog("\nTA controlador\n");
return minimo(tiempo1,tiempo2);
}
void controlador2::dint(double t) {
printLog("CONTROLADOR delta int \n");
printLog("\nPuerto SALIDA\n");
std::stringstream v3;
	v3 << puerto_salida ;
	char const *pchar3 = v3.str().c_str();
	printLog(pchar3);
printLog(" \n");

printLog("\nE1\n");
std::stringstream v1;
	v1 << e1.c_str() ;
	char const *pchar1 = v1.str().c_str();
	printLog(pchar1);
printLog(" \n");

printLog("\nE2\n");
std::stringstream v2;
	v2 << e2.c_str() ;
	char const *pchar2 = v2.str().c_str();
	printLog(pchar2);
printLog(" \n");



if((puerto_salida == 0) && (e1.compare("Ocupado") ==0) && (tiempo1 <= tiempo2) &&
 (piso1 == destino1) && (cola1.size() == 0)){
	e1 = "Libre";
    ult_dest1 = 0;
	tiempo1 = 0;
	puerto_salida = 2;
	printLog("IF1");
}else{
	if ((puerto_salida == 0) && (e1.compare("Ocupado") ==0) && (tiempo1 <= tiempo2) &&
   	 (piso1 == destino1) && (cola1.size() != 0)){
		const long &result = cola1.front();
        destino1 = result;
        
		e1 = "Ocupado";
		cola1.pop();
		tiempo1 = 0;	
        std::stringstream v1;
	    v1 << destino1 ;
	    char const *pchar = v1.str().c_str();
	    printLog(" \n DESTINO 1111111111111 ");
	    printLog(pchar);
	    printLog(" \n");
		puerto_salida = 0;	
printLog("IF2");
	}else{
		if((puerto_salida == 0) && (e1.compare("Ocupado") ==0) && (tiempo1 <= tiempo2) &&
   	 	 (piso1 != destino1) ){
			tiempo1 = 0;
			puerto_salida = 2;printLog("IF3");//aca cambieee
		}else{
			if((puerto_salida == 1) && (e2.compare("Ocupado") == 0) && (tiempo1 > tiempo2) &&
			 (piso2 ==destino2) && (cola2.size() ==0) ){
				e2 = "Libre";
                ult_dest2 = 0;				
                tiempo2 = 0;
				puerto_salida = 2;
printLog("IF4");
			}else{
				if((puerto_salida == 1) && (e2.compare("Ocupado") == 0) && (tiempo1 > tiempo2) &&
				 (piso2 ==destino2) && (cola2.size() !=0)){
                    const long &result = cola2.front();
                    destino2 = result;
        
		            e2 = "Ocupado";
	            	cola2.pop();
	            	tiempo2 = 0;	
                    std::stringstream v1;
                    v1 << destino2 ;
	                char const *pchar = v1.str().c_str();
	                printLog(" \n DESTINO 1111111111111 ");
	                printLog(pchar);
	                printLog(" \n");
		            puerto_salida = 1;	
printLog("IF5");
				}else{
					if((puerto_salida == 1) && (e2.compare("Ocupado") ==0) && (tiempo1 > tiempo2) &&
   	 	 			 (piso2 != destino2) ){
						tiempo2 = 0;
						puerto_salida = 2;//aca cambiee
printLog("IF6");
					}else{
						if((puerto_salida == 2) && (tiempo1 == 0)){
							printLog("IF7");
							tiempo1 = INF;
							puerto_salida = 0;
						}else{
							if ((puerto_salida == 2) && (tiempo2 == 0)){
								tiempo2 = INF;
								printLog("IF7");
								puerto_salida = 1;
							}else{
								printLog("\nERROR CONTROLADOR delta int \n");
							}
						}
					}
				}
			}
		}
	}
}
}
void controlador2::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
printLog("CONTROLADOR delta ext \n");
double *aux;
aux = (double*) x.value;
if((e1.compare("Libre") == 0) && (x.port == 0) && (optimo(*aux) == 1)){
    counter_aux++;
	destino1 = *aux;
	demora1=demora1-e+*aux;
    ult_dest1 = *aux;
	e1 = "Ocupado";
	tiempo1 = 0;
	tiempo2 = tiempo2 - e;
	puerto_salida = 0;
}else{
	if((e1.compare("Ocupado") == 0) && (x.port == 0) && (optimo(*aux) == 1)){
        counter_aux++;
		tiempo1 = tiempo1 -e;
        ult_dest1 = *aux;
		cola1.push(*aux);
        
		demora1 =  demora1-e+ *aux;
		tiempo2 = tiempo2-e;
	}else{
		if((e2.compare("Libre") == 0) && (x.port == 0) && (optimo(*aux) == 2)){
            counter_aux++;
			tiempo1 = tiempo1 -e;
			destino2 = *aux ;
            ult_dest2 = *aux;			
            demora2 = demora2-e+*aux;
			e2 = "Ocupado";
			tiempo2 = 0;
			puerto_salida = 1;
		}else{
			if((e2.compare("Ocupado") == 0) && (x.port == 0) && (optimo(*aux) ==2)){
                counter_aux++;
				tiempo1 = tiempo1-e;
				tiempo2 = tiempo2-e;
                ult_dest2 = *aux;			
            	cola2.push(*aux);
				demora2 = demora2-e+ *aux;
			}else{
				if((e1.compare("Ocupado") == 0) && (x.port == 1) && (*aux == destino1)){
					piso1=*aux;
					demora1 = demora1-e;
					tiempo1 = 0;
					tiempo2 = tiempo2 -e;
					puerto_salida = 0;
					
				}else{
					if((e1.compare("Ocupado") == 0) && (x.port == 1) && (*aux != destino1)){
						piso1 = *aux;
						demora1 = demora1-e;
						tiempo1 = INF;
						tiempo2 = tiempo2-e;
						puerto_salida = 1;
						
					}else{
						if((e2.compare("Ocupado") == 0) && (x.port == 2) && (*aux == destino2)){
							piso2 = *aux;
							demora2 = demora2-e;
							tiempo2 = 0;
							tiempo1 = tiempo1 -e;
							puerto_salida = 1;
						}else{
							if((e2.compare("Ocupado") == 0) && (x.port == 2) && (*aux != destino2)){
								piso2 = *aux;
								demora2 = demora2-e;
								tiempo2 = INF;
								tiempo1 = tiempo1 -e;
								puerto_salida = 0;
							}else{
								printLog("\n ERROR CONTROLADOR delta ext \n");
							}
						}
					}
				}
			}
		}
	}
}
}
Event controlador2::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("\n SALIDA CONTROLADOR \n");
printLog("\nCOLA 1 SIZE");
std::stringstream v1;
	v1 << cola1.size() ;
	char const *pchar = v1.str().c_str();
	printLog(pchar);
printLog(" \n");


printLog("\nCOLA 2 SIZE");
std::stringstream v2;
	v2 << cola2.size() ;
	char const *pchar2 = v2.str().c_str();
	printLog(pchar2);
printLog(" \n");



printLog("\nPuerto SALIDA\n");
std::stringstream v3;
	v3 << puerto_salida ;
	char const *pchar3 = v3.str().c_str();
	printLog(pchar3);
printLog(" \n");
printLog("SALIDA controlador\n");

if ((puerto_salida == 0) && (piso1 == destino1)){
	salida = "Parar"; 


}else{
	if ((puerto_salida == 0) && (piso1 > destino1)){
		salida = "Abajo";
	}else{
		if ((puerto_salida == 0) && (piso1 < destino1)){
			salida = "Arriba";
		}else{
			if ((puerto_salida == 1) && (piso2 == destino2)){
				salida = "Parar";
			}else{
				if ((puerto_salida == 1) && (piso2 > destino2)){
					salida = "Abajo";
				}else{
					if ((puerto_salida == 1) && (piso2 < destino2)){
						salida = "Arriba";
					}else{
						if (puerto_salida == 2 && disponibilidad()){
							printLog("Disponibilidad1");
							salida = "Libre";
						}else{
							if (puerto_salida == 2 && !disponibilidad()){
								printLog("Disponibilidad2");
								salida = "Ocupado";							
							}else{
								printLog("ERROR CONTROLADOR: salida ");
							}
						}
					}
				}
			}
		}
	}
}


return Event(&salida , puerto_salida);

}
void controlador2::exit() {
//Code executed at the end of the simulation.

}
