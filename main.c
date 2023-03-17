/*Berenice Arzate Rueda
 * 6/03/23
 * Mediciones con ADC usando C
 *
 *	-------
 *	|	  |
 *	|	  |
 *	| ADC0|	<---input
 *	-------
 *	Descripcion
 *	-[x] ADC0 test
 *	-[x]Imprimir ADC0 9 veces
 *	-[x] Imprimir ADC n veces 
 *	*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define ADC0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

int main(int argc, char* argv[]){
	printf("Ejecutando \n");
	FILE *fp;
	//fp = fopen(ADC0, "rt");		//tr-read
	char reads[80];		//Se guarda lo que se lea 
	//fgets(reads,20,fp);		//Lee lo que esta en el puntero y guarda en reads
	//printf("%s", reads);
	if(argc!=2){
		printf("Argumentos: %d \n", argc);
		printf("Comando usado: adc-meas n \n");
		printf("n Es el numero de mediciones \n");
	}

	int n=(int)strtol(argv[1],NULL,10);

	for (int i=0;i<n;i++){
	fp = fopen(ADC0, "rt");		//tr-read
	fgets(reads,20,fp);		//Lee lo que esta en el puntero y guarda en reads
	printf("%s", reads);
	sleep(1);
	}
   printf("OK \n");	
	return 0;
}
