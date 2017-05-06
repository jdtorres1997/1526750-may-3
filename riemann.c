/**
* FILE: riemann.c
* DESCRIPTION:
* 	Implementacion de la suma de Riemann para calcular el area bajo la
*	curva.
* AUTHOR: Juan David Torres juan.torres.canon@correounivalle.edu.co
* LAST REVISED: 05-05-2017
* REFERENCES: http://mathinsight.org/calculating_area_under_curve_riemann_sums
******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // La longitud en el eje 'x'
double numRectxThread = (double)(MAXRECT/MAXTHREAD); // Cuantos hilos/rectangulo
double base_length = 0; // Variable que tiene el ancho de cada rectangulo
double sumTotal = 0; // Variable que tendra la suma total
double partialSums[MAXTHREAD]; // Variable que tien la suma parcial de c/hilo

// Funcion a la que se le calculara la integral, x^2
double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	// Su funcion debe
	// 1- Identificar que porcion de rectangulos le toca procesar a este 
	//    hilo. Eso ira en la variable 'arg'. Cree una variable 'id' para
	//    esto.
	int id = (int)arg;
	// 2- Identificar ademas en que posicion del eje 'x' se empieza a
	//    calcular el area bajo la curva de los rectangulos. Llame a esta
	//    variable 'loslimit'
	int loslimit =(int)  id*numRectxThread;
	int highlimit = (int) (id+1)*numRectxThread;
	// 3- Inicializar la posicion del vector que le corresponde a este hilo,
	//    'partialSums' a cero. Recuerde que la variable 'id' del item 1
	//    le indica que posicion en el vector le corresponde a este hilo.
	partialSums[id]=0;
	// 4- Escriba un ciclo que debe recorrer el segmento de 'x' que le 
	//    corresponde a este hilo y donde calcula el area de los rectangulos
        //    que se encuentran en este segmento. Recuerde que la variable
	//    'numRectxThread' contiene el numero de rectangulos que debe
        //    procesar cada hilo.
	for(int j=loslimit;j<highlimit;j++){
		double high = (j+1)*base_length;
		partialSums[id]+=function(high)*base_length;
	}
	// 5- El area de cada rectangulo se calcula con 
	//    'function(val) * base_length'

	printf("sum: %lf\n", partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	// Definir dos vectors, 
	// uno usado para almacenar los identificadores de los hilos creados
	// (pthread_t) y el segundo para almacenar los valores 0, 1, 2, etc. 
	// que son los identificadores de los hilos que serviran para determinar
	// que bloque de rectangulos se va a procesar
	
	int taskids[MAXTHREAD];
	pthread_t threadsid[MAXTHREAD];
	base_length = length/MAXRECT; // esta variable contiene el ancho de
				      // cada base de cada rectangulo
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);
	// Creacion de los hilos que calcularan el area bajo la curva
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		// Inserte la linea de codigo para crear los hilos, los 
		// argumentos son: 
		// - threads
		// - NULL
		// - calcular
		// - taskids
		pthread_create(&threadsid[i],NULL,calcular,(void*)taskids[i]);
	}
	// Ciclo donde se espera el resultado de cada hilo
	for (int i = 0; i < MAXTHREAD; i++) {
		// Inserte la funcion que espera por la terminacion de un hilo.
		// Esta funcion recibe dos argumentos
		// - threads
		// - NULL
		pthread_join(threadsid[i],NULL);

		sumTotal += partialSums[i];
	}
	printf("Suma total %g\n",sumTotal);
	pthread_exit(NULL);
}
