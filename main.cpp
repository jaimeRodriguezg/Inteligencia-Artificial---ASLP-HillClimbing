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
using namespace std;

//variable global
bool flag = true;

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
      int *planes;
      int *times;
      bool solucionFactible;
   
   public: 
      Representation(int);
      void read();
      void setPlanes(int* );
      void setTimes(int, int);
      void setCostoTotal(int);
      void setSolucionFactible(bool);
};

Representation::Representation(int _n_aviones){
   n_aviones = _n_aviones;
   planes = (int *)malloc(n_aviones*sizeof(int));
   times = (int *)malloc(n_aviones*sizeof(int));
   solucionFactible = true;
}

void Representation::read(){
   cout << "El costo total es" << costoTotal << endl;
   for (int i = 0 ; i < n_aviones ; i++){
      cout << "El tiempo del avión " << planes[i] << " es " << times[i] << endl;
   }
}
void Representation::setPlanes(int* _planes){
   planes = _planes;  

}
void Representation::setTimes(int position ,int time){
   times[position] = time;
}
void Representation::setCostoTotal(int _costoTotal){
   costoTotal = _costoTotal;
}
void Representation::setSolucionFactible(bool _solucionFactible){
   solucionFactible = _solucionFactible;
}

class Greedy{
   private:
      int n_aviones;
      int costo_total;
      int tiempo_dinamico;
      int* lista_indices_aviones;
      int contador_elemntos_indice;
      Representation Sc = Representation(10);
      Airplane *airplanes;
   public:
      Greedy (int, Airplane* ); 
      
      void startAlgorithm();
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
   int* _S_ij = airplanes[0].getS_ij();
   for (int i = 0 ; i < n_aviones ; i++){
      cout << "El valor del índice: " << i << " es: " << _S_ij[i] << endl;
   }
}


void Greedy::startAlgorithm(){
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
   for (int i = 0 ; i < n_aviones - 1  ; i++){
      miopeFunction(i);
   }
   Sc.setPlanes(lista_indices_aviones);
   Sc.setCostoTotal(costo_total);
   Sc.read();

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
   int min_costo = 9999999999;
   int min_costo_no_factible = 9999999999;
   int costo_total_local;
   int indice_final_menor;
   int indice_final_menor_no_factible;
   int elemnto_a_verificar = lista_indices_aviones[posicion_elemento_a_iterar];
   int iterar = n_aviones - contador_elemntos_indice;
   int tiempo_total;
   bool factibilidad = false;
   for(int i = 0 ; i < n_aviones ; i++){
         if (checkIfExist(i,contador_elemntos_indice)){
            //no esta en la lista
            // calcular el tiempo, factibilidad y costo
            int tiempo_ideal = airplanes[elemnto_a_verificar].getTi();
            cout << "El tiempo ideal es " << tiempo_ideal << endl; 
            int separacion = airplanes[elemnto_a_verificar].get_S_ij(i);
            cout << "El valor de i es "<< i << " y el valor de la separación entre " << elemnto_a_verificar << " y " << i  << " es " << separacion << endl;
            tiempo_total = tiempo_dinamico + separacion;
            cout << "El tiempo total a iterar entre el avión " << elemnto_a_verificar << " y " << i << " es: " << tiempo_total << endl;
            int tiempo_minimo = airplanes[i].getEi();
            int tiempo_max = airplanes[i].getLi();
            cout << "El tiempo minimo del avion " << i << " es: " << tiempo_minimo << endl;
            cout << "El tiempo max del avion " << i << " es: " << tiempo_max << endl;
            cout << "El tiempo_dinamico del avion " << i << " es: " << tiempo_dinamico << endl;
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
               cout << "----------------------------------------------------------------------" << endl;
               cout << "El avion " << i << " es factible" << endl;
               //calculamos el costo


               costo_total_local = abs(tiempo_total-tiempo_ideal_aux)*costo_avion_iterar;
               cout << "El costo total local es " << costo_total_local << endl;
               cout << "min_costo es " << min_costo << endl;
               // si hay más de una opción factible, guardamaos el costo de esa funcion factible y el indice
               if (costo_total_local < min_costo ){
                  cout << "entre" << endl;
                  min_costo = costo_total_local;
                  indice_final_menor = i;
                  
               }
               cout << "----------------------------------------------------------------------" << endl;

            }else{
               cout << "''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" << endl;
               cout << "El avion " << i << " NO es factible" << endl;
               // si ya no quedan mas soluciones
               costo_total_local = abs(tiempo_total-tiempo_ideal_aux)*costo_avion_iterar*1.1;
               cout << "El costo total local es " << costo_total_local << endl;
               cout << "min_costo no factible es " << min_costo_no_factible << endl;
               // si hay más de una opción factible, guardamaos el costo de esa funcion factible y el indice
               if (costo_total_local < min_costo_no_factible ){
                  cout << "entre" << endl;
                  min_costo_no_factible = costo_total_local;
                  indice_final_menor_no_factible = i;
                  cout << "min_costo_no_factible "<< min_costo_no_factible <<endl;
                  
               }
               cout << "''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" << endl;

            }

         }
   }
   //si no quedaron soluciones factibles
   if(!factibilidad){
      cout << "------------------------------------ ENTRO A NO FACTIBLE ------------------------------------" << endl;
      lista_indices_aviones[contador_elemntos_indice] = indice_final_menor_no_factible;
      cout << "min_costo_no_factible " << min_costo_no_factible << endl;
      costo_total = costo_total + min_costo_no_factible;
      Sc.setSolucionFactible(false);
   }else{

      lista_indices_aviones[contador_elemntos_indice] = indice_final_menor;
      cout << "min_costo " << min_costo << endl;
      costo_total = costo_total + min_costo;
   }
   Sc.setTimes(indice_final_menor, tiempo_dinamico);
   tiempo_dinamico = tiempo_total;

   

   cout << "*****************************************" <<endl;
   cout << "indice final menor es " << indice_final_menor << endl;
   cout << "El tiempo del avion " << indice_final_menor << " es " << tiempo_dinamico << endl;
   cout << "El costo total  es " << costo_total << endl;
   cout << "contador elemento indice es " << contador_elemntos_indice <<endl;
   contador_elemntos_indice = contador_elemntos_indice + 1 ;
   cout << "Lista de indices de aviones es " <<endl;
   for (int i = 0 ; i <= contador_elemntos_indice ; i++){
      cout << lista_indices_aviones[i] << endl;
   }
   cout << "*****************************************" <<endl;
   

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
   cout << "El tiempo ideal mínimo es " << min << endl;
   cout << "El índice del avión es " << indice << endl;

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
   public:
      HillClimbingMM(string);
      void readFile();
      void startAlgorithm();
      void checkSolution();
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
   cout << "El número de aviones es: ";
   cout << n_aviones << endl;
   airplanes =(Airplane * )malloc(n_aviones*sizeof(Airplane));
   
   // Obtener línea de archivo, y almacenar contenido en "linea"

   while (getline(archivo, linea)) {
      cout << "Una línea: ";
      cout << linea << endl;
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
         int _Ei = airplanes[contador_aviones].getEi();
         int _Ti = airplanes[contador_aviones].getTi();
         int _Li = airplanes[contador_aviones].getLi();
         int _gi = airplanes[contador_aviones].getgi();
         int _hi = airplanes[contador_aviones].gethi();         
         cout << "Los datos del avion " << contador_aviones << " son: " << endl;

         cout << "_Ei: " << _Ei << endl;
         cout << "_Ti: " << _Ti << endl;
         cout << "_Li: " << _Li << endl;
         cout << "_gi: " << _gi << endl;
         cout << "_hi: " << _hi << endl;
         
         int* _S_ij = airplanes[contador_aviones].getS_ij();

         for (int i = 0 ; i < n_aviones ; i++){
            cout << "El valor del índice: " << i << " es: " << _S_ij[i] << endl;
         }

         contador_aviones = contador_aviones + 1;  
      }
      //  free(S_ij);
   }
}

void HillClimbingMM::startAlgorithm(){
   cout << "Hil Climbin MM starting " << endl;
   //comienza el crónometro para contabilizar el tiempo el cual se demora el algoritmo
   auto start= chrono::high_resolution_clock::now();

   //Comienza el algoritmo de Greedy para obtener una solución inicial 
   Greedy Sc (n_aviones, airplanes);
   Sc.startAlgorithm();
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
   string filename = argv[1];

   if(existFile(filename)){
      cout << "El archivo existe" << endl;
      // se incializa clase de hillClimbing
      HillClimbingMM HCMM(filename);
      HCMM.readFile();
      //comienza el algoritmo de hill climbing
      HCMM.startAlgorithm();

   }else{
      cout << "El archivo: " << filename << " no se encuentra o no existe" << endl;
      exit(1);
   }

   return 0;
}
