/**
-----------------Ejercicio imprimir  hola n------------------------------------

Programa que crea la cantidad de hilos que le entren por parámetro (Debe indicarse), 
y cada uno de ellos imprime un hola n, donde n es el identificador propio del hilo, 
Preguntando este con pthread_self.

Autor: Juan David Torres
Fecha: Mayo 4 2017

**/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_hola(void*);

int main(int argc, char *argv[]){

	int nthreads = 0;
	if(argc != 2){
		printf("Por favor digite un numero de hilos a usar\n");
		printf("\t%s <numhilos>\n",argv[0]);
		exit(-1);
	}
	
	nthreads = atoi(argv[1]);
	
	pthread_t tids[nthreads];
	int j;

	for(j=0;j<nthreads;j++) {
		pthread_create(&tids[j], NULL, print_hola, NULL);
	}
	int i;	
	for(i=0;i<nthreads;i++) {
		pthread_join(tids[i],NULL);

	}
	
	return 0;

}

void* print_hola(void* null){
	long ide = pthread_self();
	if(ide<0)
		ide=ide*(-1);
	printf("hola %ld\n",ide);
	pthread_exit(NULL);

}
