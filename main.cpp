#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include<cstdio>
#include <chrono> 
#include <cmath>
#include <bits/stdc++.h> 
#include <algorithm>
#include <iterator>
using namespace std;

//variable global
bool flag = true;
int n_aviones_global;
int restarts;

class Airplane {
   private:
      int E_i; //Riempo más temprano de aterrizaje para el avión
      int T_i; //Riempo ideal de aterrizaje para el avión
      int L_i; //Riempo más tardío de aterrizaje para el avión
      int g_i; //Penalización del avión por aterrizar antes de T_i
      int h_i; //Penalización del avión por aterrizar después de L_i
      int *S_ij; //arreglo con la separación con los otros aviones
      int T_f; // tiempo final de aterrizaje del avión
      int C_f; // Costo final del avión por su aterrizaje

   public:
      int getEi();
      int getTi();
      int getLi();
      int getgi();
      int gethi();
      int getTf();
      int getCf();
      int* getS_ij();
      int get_S_ij(int);
      void setETLgh(int, int, int, int, int);
      void setSC_ij(int*, int);
      void setTf(int);
      void setCf(int);
};

//Funcion para obtener el elemento Ei de la clase Airplane
int Airplane::getEi(){
   return  E_i;
}
//Funcion para obtener el elemento Ti de la clase Airplane
int Airplane::getTi(){
   return  T_i;
}
//Funcion para obtener el elemento Li de la clase Airplane
int Airplane::getLi(){
   return  L_i;
}
//Funcion para obtener el elemento gi de la clase Airplane
int Airplane::getgi(){
   return  g_i;
}
//Funcion para obtener el elemento hi de la clase Airplane
int Airplane::gethi(){
   return  h_i;
}
//Funcion para obtener el elemento Tf de la clase Airplane
int Airplane::getTf(){
   return  T_f;
}
//Funcion para obtener el elemento Cf de la clase Airplane
int Airplane::getCf(){
   return  C_f;
}
// Función para obtener la lista de las separaciones de los aviones por avion
int* Airplane::getS_ij(){
   return S_ij;
}
//devuelve el valor de la separación del avión con el avión j
int Airplane::get_S_ij(int j){
   return S_ij[j];
}
// Función para setear el los valores E_i T_i L_i g_i h_i
void Airplane::setETLgh(int _E_i, int _T_i, int _L_i, int _g_i, int _h_i){
   E_i = _E_i;
   T_i = _T_i;
   L_i = _L_i;
   g_i = _g_i;
   h_i = _h_i;
}
// Función para setear la lista de la separación de los aviones
void Airplane::setSC_ij(int* _S_ij, int n_aviones){
   S_ij =(int*)malloc(sizeof(int)*n_aviones);
   S_ij = _S_ij;
}
// setea la variable T_f de la clase Airplane
void Airplane::setTf(int _Tf){
   T_f = _Tf;
}
// setea la variable C_f de la clase Airplane
void Airplane::setCf(int _Cf){
   C_f = _Cf;
}


class Representation {
   private:
      int costoTotal;
      int n_aviones;
      int *airplanes;
      int *times;
      bool solucionFactible;
   
   public: 
      Representation(int);
      Representation(const Representation& other);//copy constructor
      void read();
      void setAirplanes(int* );
      void setTimes(int, int);
      void setAllTimes(int *);
      void setCostoTotal(int);
      void setSolucionFactible(bool);
      int* getAirplanes();
      int* getTimes();
      int getsetCostoTotal();
};

Representation::Representation(int _n_aviones){
   n_aviones = _n_aviones;
   airplanes = (int *)malloc(n_aviones*sizeof(int));
   times = (int *)malloc(n_aviones*sizeof(int));
   solucionFactible = true;
}
Representation::Representation(const Representation &other){
      costoTotal = other.costoTotal;
      n_aviones = other.n_aviones;
      solucionFactible = other.solucionFactible;
      airplanes = (int *)malloc(n_aviones*sizeof(int));
      times = (int *)malloc(n_aviones*sizeof(int));
      for (int i = 0 ; i < n_aviones ; i++){
         airplanes[i] = other.airplanes[i];
         times[i] = other.times[i];
      }
}

void Representation::read(){
   cout << "El costo total es: " << costoTotal << endl;
   for (int i = 0 ; i < n_aviones ; i++){
      cout << "El tiempo del avión " << airplanes[i] << " es " << times[i] << endl;
   }
}
void Representation::setAirplanes(int* _planes){
   airplanes = _planes;  

}
void Representation::setTimes(int position ,int time){
   times[position] = time;
}

void Representation::setAllTimes(int* _times){
   times = _times;
}

void Representation::setCostoTotal(int _costoTotal){
   costoTotal = _costoTotal;
}
void Representation::setSolucionFactible(bool _solucionFactible){
   solucionFactible = _solucionFactible;
}
int* Representation::getAirplanes(){
   return airplanes;
}
int* Representation::getTimes(){
   return times;
}
int Representation::getsetCostoTotal(){
   return solucionFactible;
}

class Greedy{
   private:
      int n_aviones;
      int costo_total;
      int tiempo_dinamico;
      int* lista_indices_aviones;
      int contador_elemntos_indice;
      Representation Sc = Representation(n_aviones_global);
      Airplane *airplanes;
   public:
      Greedy (int, Airplane* ); 
      
      Representation startAlgorithm();
      void miopeFunction(int);
      bool checkIfExist(int, int);
      int shortestIdealTime();
};

Greedy:: Greedy(int _n_aviones, Airplane* _airplanes){
   cout << "Greedy starting " << endl;
   n_aviones = _n_aviones;  
   costo_total = 0;
   airplanes =(Airplane * )malloc(n_aviones*sizeof(Airplane));
   airplanes = _airplanes;
}


Representation Greedy::startAlgorithm(){
   lista_indices_aviones = (int *)malloc(n_aviones*sizeof(int));
   int indice = shortestIdealTime();
   int min = airplanes[indice].getTi();
   //se guarda el avión el menor tiempo ideal en la lista de índices
   contador_elemntos_indice = 0;
   lista_indices_aviones[contador_elemntos_indice] = indice;
   tiempo_dinamico = airplanes[indice].getTi();
   Sc.setTimes(contador_elemntos_indice, tiempo_dinamico); 
   contador_elemntos_indice += 1;
   cout << min << endl;
   for (int i = 0 ; i < n_aviones -1  ; i++){
      miopeFunction(i);
   }
   Sc.setAirplanes(lista_indices_aviones);
   Sc.setCostoTotal(costo_total);
   return Sc;
}

//verifica si un avion existe en la lista de aviones checkeados por greedy
bool Greedy::checkIfExist(int i, int limite){
   for (int j = 0 ; j <= limite ; j++ ){
      if (i == lista_indices_aviones [j]){
         return false;
      }
   }
   return true;
}

void Greedy:: miopeFunction(int posicion_elemento_a_iterar){
   int min_costo = 99999;
   int min_costo_no_factible = 99999;
   int costo_total_local;
   int indice_final_menor;
   int indice_final_menor_no_factible;
   int elemnto_a_verificar = lista_indices_aviones[posicion_elemento_a_iterar];
   int tiempo_total;
   bool factibilidad = false;
   for(int i = 0 ; i < n_aviones ; i++){
         if (checkIfExist(i,contador_elemntos_indice)){
            //no esta en la lista
            // calcular el tiempo, factibilidad y costo
            int separacion = airplanes[elemnto_a_verificar].get_S_ij(i);
            tiempo_total = tiempo_dinamico + separacion;
            int tiempo_minimo = airplanes[i].getEi();
            int tiempo_max = airplanes[i].getLi();
            int tiempo_ideal_aux = airplanes[i].getTi();
            int costo_avion_iterar;
            //se obtiene el costo g_i
            if (tiempo_total >= tiempo_minimo){
               costo_avion_iterar = airplanes[i].getgi();
            }else{
               //se obtiene el costo h_i
               costo_avion_iterar = airplanes[i].gethi();
            }
            //revisa factibilidad
            if (tiempo_total >= tiempo_minimo && tiempo_total <= tiempo_max){
               factibilidad = true;
               //calculamos el costo
               //costo_total_local = abs(tiempo_total-tiempo_ideal_aux)*costo_avion_iterar;
               if (tiempo_total-tiempo_ideal_aux == 0){
                  costo_total_local = 0 ;
               }else{

                  costo_total_local = costo_avion_iterar;
               }
               // si hay más de una opción factible, guardamaos el costo de esa funcion factible y el indice
               if (costo_total_local < min_costo ){
                  min_costo = costo_total_local;
                  indice_final_menor = i;
               }
            }else{
               // si ya no quedan mas soluciones
               //costo_total_local = abs(tiempo_total-tiempo_ideal_aux)*costo_avion_iterar*1.1;
               costo_total_local = costo_avion_iterar*1.1;
               // si hay más de una opción factible, guardamaos el costo de esa funcion factible y el indice
               if (costo_total_local < min_costo_no_factible ){
                  min_costo_no_factible = costo_total_local;
                  indice_final_menor_no_factible = i;
                  tiempo_total = tiempo_minimo;   
               }
            }
         }
   }
   //si no quedaron soluciones factibles
   if(!factibilidad){
      lista_indices_aviones[contador_elemntos_indice] = indice_final_menor_no_factible;
      costo_total = costo_total + min_costo_no_factible;
      Sc.setSolucionFactible(false);
   }else{

      lista_indices_aviones[contador_elemntos_indice] = indice_final_menor;
      costo_total = costo_total + min_costo;
   }
   Sc.setTimes(posicion_elemento_a_iterar+1, tiempo_total);
   tiempo_dinamico = tiempo_total;
   contador_elemntos_indice = contador_elemntos_indice + 1 ;
}

int Greedy::shortestIdealTime(){
   int min = 999999;
   int indice = 0;
   for (int i = 0 ; i < n_aviones ; i++){
      int tiempo_ideal = airplanes[i].getTi();
      if(tiempo_ideal < min ){
         min = tiempo_ideal;
         indice = i;
      }
   }
   return indice;
}


class HillClimbingMM{
   private:
      int n_aviones;
      Airplane *airplanes; //arreglo de todos los aviones con su correpsondiente clase
      string filename;
      bool local;
      string sc;
      string sb;
      Representation Sc = Representation(n_aviones_global);
      Representation Sbest = Representation(n_aviones_global);
      Representation* neighboors; 
   public:
      HillClimbingMM(string);
      void readFile();
      void startAlgorithm();
      void checkSolution();
      Representation generetareNeighboors(Representation);
      void clear();
};


//constructor de la clase HillClimbingMM
HillClimbingMM::HillClimbingMM(string _filename){
   filename = _filename;
   local = false;
}

//Se lee el archivo y se crea una lista de aviones de la clase Airplane con el dato de cada avión.
void HillClimbingMM::readFile(){
   int contador_aviones = 0;
   vector<string> lines;
   ifstream archivo(filename.c_str());
   string linea;
   getline(archivo, linea);
   n_aviones = stoi(linea);
   n_aviones_global = n_aviones;
   airplanes =(Airplane * )malloc(n_aviones*sizeof(Airplane));
   
   // Obtener línea de archivo, y almacenar contenido en "linea"
   while (getline(archivo, linea)) {
      lines.push_back(linea);
      string word;
      istringstream ss(linea);
      int contador = 0;
      int contador2 = 0;
      int E_i;
      int T_i;
      int L_i;
      int g_i;
      int h_i;
      int *S_ij;
      S_ij =(int*)malloc(sizeof(int)*n_aviones);
      if(flag){
         while (ss >> word){
            if (contador == 0){
               //E_i
               E_i = stoi(word);
            }else if(contador == 1){
               //T_i
               T_i = stoi(word);
            }else if(contador == 2){
               //L_i
               L_i = stoi(word);
            }else if(contador == 3){
               //g_i
               g_i = stoi(word);
            }else if(contador == 4){
               //_h_i
               h_i = stoi(word);     
            }
            contador = contador + 1 ;  
         }
         
         airplanes[contador_aviones].setETLgh(E_i,T_i,L_i,g_i,h_i);
         flag = false;
      // se lee las separaciones
      }else {
         while (ss >> word){
            S_ij[contador2] = stoi(word);
            contador2 = contador2 + 1;
         }
         airplanes[contador_aviones].setSC_ij(S_ij, n_aviones); 
         flag = true; 
         contador_aviones = contador_aviones + 1;  
      }
   }
}

//El movimiento que se aplica es aplicar el tiempo ideal a cada avión. Por ejemplo
//                                                [2,3,4,5,9,0,6,7,8,9,1]
// si se tiene como solucion inicial lo siguiente [98,106,114,122,130,145,156,161,169,195]
// a través del movimiento quedaría : (a cada avión se le asigna su tiempo ideal y el resto de los aviones quedan con el tiempo de la solución inicial)
//["98",106,114,122,130,145,156,161,169,195]
//[98,"106",114,122,130,145,156,161,169,195]
//[98,106,"123",122,130,145,156,161,169,195]
//[98,106,114,"135",130,145,156,161,169,195]
//[98,106,114,122,"155",145,156,161,169,195] .......
Representation HillClimbingMM::generetareNeighboors(Representation _Sc){
   _Sc.read();
   neighboors =(Representation * )malloc(n_aviones*sizeof(Representation));

   Representation S_aux = _Sc; //se crea una copia de la clase;
   int* _airplanes = S_aux.getAirplanes();
   int* _times = S_aux.getTimes();
   for(int k = 0 ; k < n_aviones ; k++){
      cout << _times[k] << endl;
   }
   int* _times_aux;
   _times_aux =(int * )malloc(n_aviones*sizeof(int));
      for(int k = 0 ; k < n_aviones ; k++){
      _times_aux[k] = _times[k] ;
   }
   //se generan los vecinos
   for (int i = 0 ; i < n_aviones ; i++){
      int tiempo_ideal = airplanes[_airplanes[i]].getTi();
      Representation S_aux2 = S_aux;
      neighboors[i] = S_aux2;
      _times_aux[i] = tiempo_ideal;
      cout << "El tiempo ideal es " << tiempo_ideal << " y _times_aux[i] con i = " << i << " es " <<  _times_aux[i] << endl;
      neighboors[i].setTimes(i, tiempo_ideal);
   }
   cout << "------------ Neighboors ------------------" << endl;
   //recorremos los vecinos, revisamos factibilidad y obtenemos el mejor (Sn)
   for (int i = 0 ; i < n_aviones ; i++){
      Representation aux = neighboors[i];
      cout << "Vecino: " << i << endl;
      for(int j = 0 ; j <n_aviones; +j++ ){
         cout << "El tiempo del avión " << aux.getAirplanes()[j] << " es " << aux.getTimes()[j] << endl;
      }
   }
   cout << "------------ Neighboors ------------------" << endl;
   S_aux.read();
   _Sc.read();
}

void HillClimbingMM::startAlgorithm(){
   cout << "Hil Climbin MM starting " << endl;
   //comienza el crónometro para contabilizar el tiempo el cual se demora el algoritmo
   auto start= chrono::high_resolution_clock::now();

   //Comienza el algoritmo de Greedy para obtener una solución inicial 
   Greedy greedy (n_aviones, airplanes);
   Sc = greedy.startAlgorithm();
   Sc.read();
   //Se incializa Sbest con el valor inicial
   Sbest = Sc ;
   //recorremos por todos los restarts 
   for ( int i = 0 ; i < restarts ; i++){
      local = false;
      while(!local){
         //Generamos el vecinadario a través de un movimiento y seleccionamos un punto del vecinadrio
         Representation Sn = generetareNeighboors(Sc);
         local = true;



         //
      }
   }
   cout << "sad" <<endl;
   Sbest.read();   



   auto stop= chrono::high_resolution_clock::now();
   auto duration= chrono::duration_cast<chrono::microseconds>(stop-start);
   cout << "Tiempo de ejecución: "<< duration.count()<<" microsegundos"<<endl;
}


// Verifica si el archivo entregado existe o no
bool existFile(string path){
   ifstream file;
   file.open(path.c_str());
   return bool(file);
}

int main(int argc, char *argv[]){

   
   if(argc == 1 ){
      cout << "Falta ingresar la ruta del archivo" << endl;
      exit(1);
   }
   //no ingreso la cantidad de restarts, se setea como deafult 1
   if (argc == 2){
      restarts = 1;
   }
   if (argc == 3){
      restarts = stoi(argv[2]);
   }

   string filename = argv[1];

   if(existFile(filename)){
      // se incializa clase de hillClimbing
      HillClimbingMM HCMM(filename);
      //se lee los archivos y se crean las clases correspondientes
      HCMM.readFile();
      //comienza el algoritmo de hill climbing
      HCMM.startAlgorithm();

   }else{
      cout << "El archivo: " << filename << " no se encuentra o no existe" << endl;
      exit(1);
   }

   return 0;
}
