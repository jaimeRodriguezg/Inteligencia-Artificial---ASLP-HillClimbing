#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include<cstdio>
#include <chrono> 
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
   
   public: 
      void read();
};

class Greedy{
   private:
      int n_aviones;
      int costo_total;
      int* lista_indices_aviones;
      Airplane *airplanes;
   public:
      Greedy (int, Airplane* ); 
      void startAlgorithm();
      void miopeFunction();
      int shortestIdealTime();

      
};

Greedy:: Greedy(int _n_aviones, Airplane* _airplanes){
   cout << "Greedy starting " << endl;
   n_aviones = _n_aviones;
   airplanes =(Airplane * )malloc(n_aviones*sizeof(Airplane));
   airplanes = _airplanes;
}


void Greedy::startAlgorithm(){
   int contador = 0;
   lista_indices_aviones = (int *)malloc(n_aviones*sizeof(int));
   int indice = shortestIdealTime();
   int min = airplanes[indice].getTi();
   cout << min << endl;
   for (int i = 0 ; i < n_aviones ; i++){
      miopeFunction();
   }

}

void Greedy:: miopeFunction(){

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
         // free(S_ij);
         cout << "x1" << endl;
         
      }
         cout << "x2" << endl;
       free(S_ij);
   }
         cout << "x3" << endl;
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
      cout << "paseeeeee" << endl;
      //comienza el algoritmo de hill climbing
      HCMM.startAlgorithm();

   }else{
      cout << "El archivo: " << filename << " no se encuentra o no existe" << endl;
      exit(1);
   }

   return 0;
}
