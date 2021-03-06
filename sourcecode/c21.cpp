#include "c21.h"
double c21::minimo(double val1, double val2){
if (val1 <= val2){
	return val1;
}else{
	return val2;
}
}
bool c21::disponibilidad(){
	return (e1.compare("Libre") == 0 || e2.compare("Libre") == 0);
}
double c21::optimo(int t){
    if (t%2==0){
        return 1;
    }else{
        return 2;
    }
}
bool c21::find(std::deque<double> list, double elem){
    std::deque<double>::iterator it = list.begin();    
    while (it != list.end()){   
        if(*it++ == elem){
         return true;
        }    
    }
    return false;
}

void c21::init(double t,...) {
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

//clear the files
myfile.open ("c21_cola1_in.csv");
myfile << "";
myfile.close();
myfile.open ("c21_cola1_out.csv");
myfile << "";
myfile.close();
myfile.open ("c21_cola2_in.csv");
myfile << "";
myfile.close();
myfile.open ("c21_cola2_out.csv");
myfile << "";
myfile.close();
}
double c21::ta(double t) {
//This function returns a double.
printLog("\nTA controlador\n");
return minimo(tiempo1,tiempo2);
}
void c21::dint(double t) {
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
		cola1.pop_front();

        //manage c21_out.csv
        std::stringstream e_string;
        e_string<< t;
        char const *e_char = e_string.str().c_str();
        myfile.open ("c21_cola1_out.csv",std::ios::app);
        myfile << e_char;
        myfile <<"\n";
        myfile.close();

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
	            	cola2.pop_front();

                    //manage c21_out.csv
                    std::stringstream e_string;
                    e_string<< t;
                    char const *e_char = e_string.str().c_str();
                    myfile.open ("c21_cola2_out.csv",std::ios::app);
                    myfile << e_char;
                    myfile <<"\n";
                    myfile.close();

	            	tiempo2 = 0;	
                    std::stringstream v1;
                    v1 << destino2 ;
	                char const *pchar = v1.str().c_str();
	                printLog(" \n iff 2211111111111 ");
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
void c21::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
printLog("CONTROLADOR delta ext \n");
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
double *aux;
aux = (double*) x.value;
if((e1.compare("Libre") == 0) && (x.port == 0) && (optimo(counter_aux) == 1)){
    counter_aux++;
	destino1 = *aux;
	e1 = "Ocupado";
	tiempo1 = 0;
	tiempo2 = tiempo2 - e;
	puerto_salida = 0;
    demora1 = abs(*aux-piso1)*2;
    if (piso2 != destino2){
        demora2 = demora2 -e ;
    }
    ult_dest1 = *aux;

}else{
	if((e1.compare("Ocupado") == 0) && (x.port == 0) && (optimo(counter_aux) == 1)){
        tiempo1 = tiempo1 -e;
        if (!find(cola1,*aux)){
		    cola1.push_back(*aux);

            //manage c21_out.csv
            std::stringstream e_string;
            e_string<< t;
            char const *e_char = e_string.str().c_str();
            myfile.open ("c21_cola1_in.csv",std::ios::app);
            myfile << e_char;
            myfile <<"\n";
            myfile.close();

            counter_aux++;
            demora1 =  demora1-e+ (abs(*aux-ult_dest1)*2);
            ult_dest1 = *aux;
            if (piso2 != destino2){
                demora2 = demora2 -e ;
            }		
        }
		tiempo2 = tiempo2-e;
	}else{
		if((e2.compare("Libre") == 0) && (x.port == 0) && (optimo(counter_aux) == 2)){
            counter_aux++;
			tiempo1 = tiempo1 -e;
			destino2 = *aux ;
            ult_dest2 = *aux;			
			e2 = "Ocupado";
			tiempo2 = 0;
			puerto_salida = 1;
            demora2 = abs(*aux-piso2)*2;
            if (piso1 != destino1){
                demora1 = demora1 -e ;
            } 
		}else{
			if((e2.compare("Ocupado") == 0) && (x.port == 0) && (optimo(counter_aux) ==2)){
                tiempo1 = tiempo1-e;
				tiempo2 = tiempo2-e;
                printLog("ifffffff1");
                if (!find(cola2,*aux)){            	
                    cola2.push_back(*aux);

                      //manage c21_out.csv
                    std::stringstream e_string;
                    e_string<< t;
                    char const *e_char = e_string.str().c_str();
                    myfile.open ("c21_cola2_in.csv",std::ios::app);
                    myfile << e_char;
                    myfile <<"\n";
                    myfile.close();

                    counter_aux++;
					demora2 = demora2-e+ (abs(*aux-ult_dest2)*2);
                    ult_dest2 = *aux;	
                    if (piso1 != destino1){
                        demora1 = demora1 -e ;
                    } 
                }
			}else{
				if((e1.compare("Ocupado") == 0) && (x.port == 1) && (*aux == destino1)){
					piso1=*aux;
                    if (demora1!=0){
                        demora1 = demora1-e;
                    }
					if (demora2!=0){
                        demora2 = demora2-e;
                    }
					tiempo1 = 0;
					tiempo2 = tiempo2 -e;
					puerto_salida = 0;
					
				}else{
					if((e1.compare("Ocupado") == 0) && (x.port == 1) && (*aux != destino1)){
						piso1 = *aux;
                        if (demora1!=0){
                            demora1 = demora1-e;
                        }
						if (demora2!=0){
                            demora2 = demora2-e;
                        }
                        
						tiempo1 = INF;
						tiempo2 = tiempo2-e;
						puerto_salida = 1;
						
					}else{
						if((e2.compare("Ocupado") == 0) && (x.port == 2) && (*aux == destino2)){
							piso2 = *aux;
							if (demora1!=0){
                                demora1 = demora1-e;
                            }
						    if (demora2!=0){
                                demora2 = demora2-e;
                            }
							tiempo2 = 0;
							tiempo1 = tiempo1 -e;
							puerto_salida = 1;
                            
						}else{
							if((e2.compare("Ocupado") == 0) && (x.port == 2) && (*aux != destino2)){
								piso2 = *aux;
								if (demora1!=0){
                                    demora1 = demora1-e;
                                }
						        if (demora2!=0){
                                    demora2 = demora2-e;
                                }
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
Event c21::lambda(double t) {
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
void c21::exit() {
//Code executed at the end of the simulation.

}
