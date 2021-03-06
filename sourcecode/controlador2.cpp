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

bool controlador2::find(std::deque<double> list, double elem){
    std::deque<double>::iterator it = list.begin();    
    while (it != list.end()){   
        if(*it++ == elem){
         return true;
        }    
    }
    return false;
}
double controlador2::optimo(double t,double e){
    std::stringstream v1;
    std::stringstream v3;
    std::stringstream v5;
    double vv1;
    double vv2;
        if (piso1!=destino1){	  
            vv1 = demora1-e+(abs(t-ult_dest1) * 2);  v1 << vv1 ;}else{	vv1= (abs(t-piso1) * 2);   v1 << vv1  ;}
        v3 << demora1;
if (piso1!=destino1){
        v5 << ult_dest1;}else{v5<<piso1;}
        printLog(" \n Demora ascensor 1: ");
	    char const *pchar = v1.str().c_str();
        char const *pchar3 = v3.str().c_str();
	    char const *pchar5 = v5.str().c_str();
	    printLog(pchar);
	    printLog(" \n");
        printLog("Demora1: ");
        printLog(pchar3);
        printLog("\n UltDest: ");
        printLog(pchar5);
                    std::stringstream v2;
            std::stringstream v4;
            std::stringstream v6;
        v4 << demora2;
if (piso2!=destino2){ 
           v6 << ult_dest2;}else{v6<<piso2;}
        char const *pchar4 = v4.str().c_str();
	    char const *pchar6 = v6.str().c_str();
        printLog(" \n Demora ascensor 2: ");
        if (piso2!=destino2){   
vv2 =  demora2-e+(abs(t-ult_dest2) * 2);    v2 << vv2 ;}else{   vv2= (abs(t-piso2) * 2);    v2 << vv2 ;}

	    char const *pchar1 = v2.str().c_str();
	    printLog(pchar1);
	    printLog(" \n");
        printLog(" \n");
        printLog("Demora2: ");
        printLog(pchar4);
        printLog("\n UltDest2: ");
        printLog(pchar6);

    if (vv2<vv1){
        printLog("cond 22");
        return 2;
    }else{
        printLog("cond 11");
        return 1;
    }


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

//clear the files
myfile.open ("c2_cola1_in.csv");
myfile << "";
myfile.close();
myfile.open ("c2_cola1_out.csv");
myfile << "";
myfile.close();
myfile.open ("c2_cola2_in.csv");
myfile << "";
myfile.close();
myfile.open ("c2_cola2_out.csv");
myfile << "";
myfile.close();
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
		cola1.pop_front();

//manage c21_out.csv
        std::stringstream e_string;
        e_string<< t;
        char const *e_char = e_string.str().c_str();
        myfile.open ("c2_cola1_out.csv",std::ios::app);
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
                    //manage c2_out.csv
                    std::stringstream e_string;
                    e_string<< t;
                    char const *e_char = e_string.str().c_str();
                    myfile.open ("c2_cola2_out.csv",std::ios::app);
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
void controlador2::dext(Event x, double t) {
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
if((e1.compare("Libre") == 0) && (x.port == 0) && (optimo(*aux,e) == 1)){
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
	if((e1.compare("Ocupado") == 0) && (x.port == 0) && (optimo(*aux,e) == 1)){
        tiempo1 = tiempo1 -e;
        if (!find(cola1,*aux)){
		    cola1.push_back(*aux);
            //manage c2_out.csv
            std::stringstream e_string;
            e_string<< t;
            char const *e_char = e_string.str().c_str();
            myfile.open ("c2_cola1_in.csv",std::ios::app);
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
		if((e2.compare("Libre") == 0) && (x.port == 0) && (optimo(*aux,e) == 2)){
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
			if((e2.compare("Ocupado") == 0) && (x.port == 0) && (optimo(*aux,e) ==2)){
                tiempo1 = tiempo1-e;
				tiempo2 = tiempo2-e;
                printLog("ifffffff1");
                if (!find(cola2,*aux)){            	
                    cola2.push_back(*aux);
                    //manage c2_in.csv
                    std::stringstream e_string;
                    e_string<< t;
                    char const *e_char = e_string.str().c_str();
                    myfile.open ("c2_cola2_in.csv",std::ios::app);
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
