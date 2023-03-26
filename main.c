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
 *	-[x] Imprimir ADC n veces 
 *	-[x] Imprime el valor mínimo
 *	-[x] Imprime el valor máximo
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
	if(strcmp(argv[1], "help")==0){
		printf("------------------------------------------------------------------------------------------------------------------------------- \n");
		printf("El programa realiza la lectura del ADC0, la cantidad de veces que se especifique en el argumento que recibe. \n");
		printf("El argumento debe ser un número entre 500 y 1000 o la palabra 'help' si se desea consultar el este menú de ayuda. Ejemplo: \n");
		printf("./adc-meas 467 \n");
		printf("./adc-meas help \n \n");
		printf("Con los datos recolectados del ADC se calculan: \n");
		printf("* Valor mínimo \n");
		printf("* Valor máximo \n");
		printf("* Valor Medio \n");
		printf("* Mediana \n");
		printf("* Valor RMS \n \n");
		printf("Los resultados anteriores se obtienen convirtiendo el valor medido en el ADC a voltaje. \n");
		printf("Para la conversión se utilizan rangos de 0 a 4095 para el ADC y  0 a 1.8 para el voltaje. \n \n");
		printf("Por último, se realiza un histograma con los datos especificando sus rangos en los valores obtenidos en el ADC. \n");
		printf("------------------------------------------------------------------------------------------------------------------------------- \n");
		return 0;
	}

	FILE *fp;
	//fp = fopen(ADC0, "rt");		//tr-read
	char reads[80];	
	int n = (int)strtol(argv[1],NULL,10);

	if (n >= 500 && n<= 1000){
		printf("------------------------------------------------------------------------------------------------------------------------------- \n");
		printf("Ejecutando \n \n ");
	}else{
		printf("Error, Ingresa un valor entre 500 y 1000 \n");
		printf("Para más información consulta ./adc-meas help \n");
		return 2;
	}

	int i, j, aux = 0;
	int  arreglo[n];
	float sum, vmedia, med, vmedian, suma, cuad = 0.00;
	float  vmax, vmin;


	if(argc!=2){
		printf("Argumentos: %d \n", argc);
		printf("Comando usado: adc-meas n \n");
		printf("Error, n Es el numero de mediciones \n");
		printf("Prueba ./adc-meas help \n");
		return 2;
	}
	//Lectura del ADC
	for (i=0;i<n;i++){
		fp = fopen(ADC0, "rt");		//tr-read
		fgets(reads,20,fp);		//Lee lo que esta en el puntero y guarda en reads
		int valor=(int)strtol(reads,NULL,10);
		arreglo[i]=valor;
		//printf("%s \n", reads);
		sum+=arreglo[i];
		cuad = 	pow(arreglo[i], 2);
		suma+=cuad;
		sleep(0.0005);
	}

	//Valor RMS
	float division = suma / n;
	float rms = sqrt(division);
	
	//Valores máx y mín
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
	//Valor medio
	vmedia = sum / n;
	//Ordenamiento de los valores
    for (i=0; i< n; i++) {
		for (j=0; j<n-i-1; j++){
			if(arreglo[j] > arreglo[j+1]){
				aux  = arreglo[j+1];
				arreglo[j+1] = arreglo[j];
				arreglo[j] = aux;
			}
		}
    }
/*	printf("Arreglo ordenado \n");
	for (i=0; i<n; i++){
		printf("%i \n", arreglo[i]);
	}
*/
	//Mediana
	if (n%2 == 0){
		vmedian = (arreglo[n/2]+arreglo[(n-2)/2])/2;
	}
	else {
		vmedian = arreglo[(n-1)/2];
	}
/*	
	printf("El valor mínimo es %2.f \n", vmin);
	printf("El valor máximo es %2.f \n", vmax);
	printf("El valor medio es %.2f \n", vmedia);
	printf("La mediana es %.2f \n", vmedian);
	printf("El valor RMS es %.2f \n", rms);
*/	
	vmin = (vmin/4095)*1.8;
	vmax = (vmax/4095)*1.8;
	vmedia = (vmedia/4095)*1.8;
	vmedian = (vmedian/4095)*1.8;
	rms = (rms/4095)*1.8;

	printf("El valor mínimo es:  %.4f Volts \n", vmin);
	printf("El valor máximo es: %.4f Volts \n", vmax);
	printf("El valor medio es: %.4f Volts \n", vmedia);
	printf("La mediana es: %.4f Volts \n", vmedian);
	printf("El valor RMS es: %.4f Volts \n\n", rms);
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");

	int maux[16] = {0};
	int a = 16;

	for(i=0;i<n;i++){
        if (arreglo[i] <= 250){
          maux[0]+= 1;
        }else if (arreglo[i]>250 && arreglo[i]<=500){
          maux[1]+= 1;
        }else if (arreglo[i]>500 && arreglo[i]<=750){
          maux[2]+= 1;
        }else if (arreglo[i]>750 && arreglo[i]<=1000){
          maux[3]+= 1;
        }else if (arreglo[i]>1000 && arreglo[i]<=1250){
          maux[4]+= 1;
        }else if (arreglo[i]>1250 && arreglo[i]<=1500){
          maux[5]+= 1;
        }else if (arreglo[i]>1500 && arreglo[i]<=1750){
          maux[6]+= 1;
        }else if (arreglo[i]>1750 && arreglo[i]<=2000){
          maux[7]+= 1;
        }else if (arreglo[i]>2000 && arreglo[i]<=2250){
          maux[8]+= 1;
        }else if (arreglo[i]>2250 && arreglo[i]<=2500){
          maux[9]+= 1;
        }else if (arreglo[i]>2500 && arreglo[i]<=2750){
          maux[10]+= 1;
        }else if (arreglo[i]>2750 && arreglo[i]<=3000){
          maux[11]+= 1;
        }else if (arreglo[i]>3000 && arreglo[i]<=3250){
          maux[12]+= 1;
        }else if (arreglo[i]>3250 && arreglo[i]<=3500){
          maux[13]+= 1;
        }else if (arreglo[i]>3500 && arreglo[i]<=3750){
          maux[14]+= 1;
        }else{
          maux[15]+= 1;
        }
    }
	
	printf("Histograma \n \n");
	int rango = 0;
    for(i=0;i<a;i++){
		if (i==15){
			printf("[%i-%i] ", rango, 4100);
		}else
			printf("[%i-%i]  ", rango, rango+250);
		for(j=0;j<maux[i];j++){
			printf("*");
		}
		rango +=250;
		printf("\n");
    }
    printf("OK \n");	
	printf("------------------------------------------------------------------------------------------------------------------------------- \n");
	return 0;
}
