# adc-sampler

Implemente el siguiente registrador de datos para el ADC usando C para programar la función para recolectar 500-1000 muestras y calcular los datos requeridos.

![](./adc.001.jpeg)

## Acondicionamiento de la señal

Para realizar una correcta lectura en el ADC0 de la BeagleBone Black o para cualquier otro de los 6 canales se debe tener en cuenta que los ADCs tienen un rango de medición de 0 a 1.8 Volts, conectar un voltaje superior a este puede dañar la placa.


En el acondicionamiento de la señal se utilizó un generador para obtener una señal senoidal de 3 Vpp la cual se redujo a la mitad mediante el uso de un amplificador inversor aplicando la formula:

![](./formula_inversor.png)

Con un segundo amplificador inversor con resistencias de igual valor se invirtió el voltaje y por último se suma una señal de 1 V para obtener el voltaje mínimo superior a 0.

El circuito resultante se muestra a continuación.

## Conexiones 


![](./conexion.jpeg)

En la imagen anterior se muestra la conexión del circuito presentado en la sección anterior con la BeagleBone, se puede observar que en la placa se utilizan los pines `AIN0` y `GND_ADC`, este último siempre se debe conectar a la tierra de una fuente de voltaje para medir un voltaje positivo.

Para a implementación del esquemático se configuró una señal senoidal de 1.3 Vpp a 100 Hz. 

![](./generador.jpeg)

Se realizaron las conexiones en una protoboard como se muestra a continuación. 

![](/armado.jpeg)

**Nota: En la protoboard se muestran tres circuitos diferentes, el utilizado en este caso es el armado en el centro.**

## Programa
Para compilar el programa es necesario ejecutar el comando: 
```
gcc main.c -o adc-meas -lm
```
En caso de no tener instalado el compilador `gcc`, para su instalacion , utilice el comando:
``` 
sudo apt-get install gcc
```
El programa recibe un argumento donde se especifica el número de lecturas del ADC mediante el comando:
```
./adc-meas num
```
El número debe ser un valor entre `500` y `1000` o bien se puede utilizar el comando con la palabra `help` en sustitución del valor para consultar el menú de ayuda.

A partir de los datos obtenidos se calculan el valor `mínimo`, `máximo`, `medio`, `RMS` y la `mediana`, posterior a ello los datos son mapeados a voltaje y mostrados en la pantalla.
El ADC cuenta con 12 bits de resolución y un rango de mediciones de `0` a `1.8` Volts, por los cual para hacer el mapeo de los valores se utiliza la siguiente regla de conversión.

![](./voltADC.png)

### Cálculo del valor medio
Se suman todos los datos y se dividen entre el número de los mismos.

### Cálculo de la mediana
Se ordenan todos los valores de menor a mayor y en caso de ser un número impar de mediciones se toma el valor posicionado en el centro, si el número de mediciones es par se toman los dos valores centrales y se promedian.

### Cálculo del valor RMS
Para el valor RMS se toma el cuadrado de cada una de las mediciones, se promedian estos valores y se saca la raíz cuadrada de dicho promedio.

![](./rms.png)

### Histograma
Para graficar el histograma de las mediciones se utilizan `16 rangos` iniciando en 0 y sumando 250 puntos hasta completar el valor máximo que pueden tomar las mediciones que equivale a 4095, por ello el último rango abarca de 3750 a 4100. Para cada rango se dibuja un asterisco `*` por cada medición dentro del mismo.

## Resultados

