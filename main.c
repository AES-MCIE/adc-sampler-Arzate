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
 *	-[x] Imprime el valor minimo
 *	-[x] Imprime el valor maximo
 *	-[x] Imprime el valor Medio
 *	-[x] Imprime la mediana
 *	-[x] Histograma
 *	-[x] Valor RMS
 *	*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

#define ADC0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

int main(int argc, char* argv[]){
	printf("Ejecutando \n");
	FILE *fp;
	//fp = fopen(ADC0, "rt");		//tr-read
	char reads[80];		//Se guarda lo que se lea 
	//fgets(reads,20,fp);		//Lee lo que esta en el puntero y guarda en reads
	//printf("%s", reads);
	int aux = 0;
	int i, j = 0 ;
	int n = (int)strtol(argv[1],NULL,10);
	int  arreglo[n];
	float sum = 0.00;
	float vmedia = 0.00;
	int vmax;
	int vmin;
	float med = 0.00;
	float vmedian  = 0.00;
	float suma = 0.00;
	float cuad = 0.00;
	int maux[n];
	if(argc!=2){
		printf("Argumentos: %d \n", argc);
		printf("Comando usado: adc-meas n \n");
		printf("n Es el numero de mediciones \n");
	}
	
	for (i=0;i<n;i++){
		fp = fopen(ADC0, "rt");		//tr-read
		fgets(reads,20,fp);		//Lee lo que esta en el puntero y guarda en reads
		int valor=(int)strtol(reads,NULL,10);
		arreglo[i]=valor;
		printf("%s \n", reads);
		sum+=arreglo[i];
		cuad = 	pow(arreglo[i], 2);
		suma+=cuad;
		maux[i] = 1;		
		sleep(0.5);
	}
	float division = suma / n;
	float rms = sqrt(division);
	
	vmax = arreglo[0];
	vmin = arreglo[0];

	for(i=0; i<n; i++){
		if(arreglo[i] >= vmax){
			vmax = arreglo[i];
		}
		if(arreglo[i] <= vmin){
			vmin = arreglo[i];
		}
	}	
	vmedia = sum / n;

    for (i=0; i< n; i++) {
		for (j=0; j<n-i-1; j++){
			if(arreglo[j] > arreglo[j+1]){
				aux  = arreglo[j+1];
				arreglo[j+1] = arreglo[j];
				arreglo[j] = aux;
			}
		}
    }
	printf("Arreglo ordenado \n");
	for (i=0; i<n; i++){
		printf("%i \n", arreglo[i]);
	}
	
	for(i=0;i<n-1;i++){
		if (arreglo[i] == arreglo[i+1]){
			maux[i]++;
			maux[i+1] = 0;
		}
		for(j=0;j<i;j++){
			if(arreglo[i] == arreglo[j]){
				maux[i]+=maux[j];
				maux[j] = 0;
			}
		}
		
	}

	if (n%2 == 0){
		vmedian = (arreglo[n/2]+arreglo[(n-2)/2])/2;
	}
	else {
		vmedian = arreglo[(n-1)/2];
	}

	printf("El valor mínimo es %i \n", vmin);
	printf("El valor máximo es %i \n", vmax);
	printf("El valor medio es %.2f \n", vmedia);
	printf("La mediana es %.2f \n", vmedian);
	printf("El valor RMS es %.2f \n", rms);
	
	for(i=0;i<n;i++){
		if(maux[i]!=0){
			printf("[%i]  ", arreglo[i]);
			for(j=0;j<maux[i];j++){
				printf("*");
			}
		printf("\n");
		}
	}

	
    printf("OK \n");	
	return 0;
}
