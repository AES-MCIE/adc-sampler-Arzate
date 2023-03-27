# adc-sampler
Implemente el siguiente registrador de datos para el ADC usando C para programar la función para recolectar 500-1000 muestras y calcular los datos requeridos.

![](./adc.001.jpeg)

## Acondicionamiento de la señal
Para realizar una correcta lectura en el ADC0 de la BeagleBone Black o para cualquier otro de los 6 canales se debe tener en cuenta que los ADCs tienen un rango de medición de 0 a 1.8 Volts, conectar un voltaje superior a este puede dañar la placa.


En el acondicionamiento de la señal se utilizó un generador para obtener una señal senoidal de 3 Vpp la cual se redujo a la mitad mediante el uso de un amplificador inversor aplicando la formula:

Con un segundo amplificador inversor con resistencias de igual valor se invirtió el voltaje y por último se suma una señal de 1 V para obtener el voltaje mínimo superior a 0.

El circuito resultante se muestra a continuación.

## Conexiones 
![](./conexion.jpeg)

En la imagen anterior se muestra la conexión del circuito presentado en la sección anterior con la BeagleBone, se puede observar que en la placa se utilizan los pines AIN0 y GND_ADC, este último siempre se debe conectar a la tierra de una fuente de voltaje para medir un voltaje positivo.

Para a implementación del esquemático se configuró una señal senoidal de 1.3 Vpp a 100 Hz. 

![](./generador)

Se realizaron las conexiones en una protoboard como se muestra a continuación.


## Programa

## Resultados

