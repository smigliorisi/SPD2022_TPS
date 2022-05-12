
/*
 *	Trabajo Práctico 1: Cronómetro Binario
 *
 *	Al iniciar la simulacion, todos los led deben comenzar apagados.
 *	Cada 1 segundo que transcurra, se deben encender los led
 *	de acuerdo al numero que representan.
 *
 *	Ejemplo:
 *   
 *	El numero 15 (0000001111) se representaria encendiendo los 
 *	leds AMARILLO y NARANJA.
 *	Al pasar al numero 16 (0000010000), se deben apagar todos 
 *	los led anteriores y encenderse uno de los leds VERDES. 
 *	Notese, en el ejemplo los 0 representan los led apagados 
 *	y los 1 los led encendidos). 
 *   
 *	-------------------------------------------------------
 *   
 *	Al presionarse el boton START, debe iniciar el cronometro.
 *	Volver a presionarlo hace que la secuencia se detenga. 
 *  (Como si se hubiese presionado pausa).
 *	Al presionarse el boton RESET, el cronometro
 *	debe reiniciarse y arrancar de 0.
 *
 *	Tip: Modularizar la función que controla el encendido de los 
 *	LEDS y de ser posible, todo el código para evitar repetir lineas lo mas posible.
 *  Usar millis para controlar el tiempo del contador para que el cambio de los 
 *	leds encendidos sea perceptible para el ojo humano y 
 *	documentar cada función creada en el código. 
 *	Un breve comentario que diga que es lo que hace esa función
 *  y de corresponder, que retorna).
*/

//##### Una Ayudita #####
//--- Defines ---//
#define ZERO_TO_HERO 0          //? To start the counter from 0
#define BUTTON_START 2
#define BUTTON_RESET 3
#define FIRST_LED 4             //? First pin of the leds
#define LAST_LED 13             //? Last pin of the leds
#define BASE_MILLI_SECONDS 1000 //? Secods expresed in miliseconds
#define MAX_SECONDS 1023        //! Max amount of secods to show
//--- End Defines ---//


int pinout [] = {4,5,6,7,8,9,10,11,12,13};
boolean Pausa=true;                                      // Descontoar o no
boolean Pulsado=false;  // Boton pulsado, esperar a soltarlo
int estadoLed = 5;
int estadoPulsadorAntes = 0;
int i=0;
int j=0;

void setup(){	
  
   Serial.begin(9600);
	int i = 0;
  
  	pinMode (BUTTON_START,INPUT);
    pinMode (BUTTON_RESET,INPUT);
  
  for (i=0;i<10;i++){
    pinMode (pinout[i],OUTPUT);
  }
	
}

void loop(){
  int i =0;
  int j =0;
  int estadoPulsador = digitalRead(BUTTON_START);
  int estadoPulsadorAntes=0;
  int reset=digitalRead(BUTTON_RESET);

  while (digitalRead(BUTTON_START)==1 && estadoPulsadorAntes==0){
  	for (i=0;i<1023;i++){ // ITERO TODOS LOS SEGUNDOS NECESARIOS HASTA CONSEGUIR 1111111111
      Serial.print(i,BIN);
    	for (j=0;j<10;j++){ // ITERO LOS LEDS
 //       if (digitalRead(BUTTON_RESET)==LOW){
      	   if (((i>>j)&1)==1){ //BIT SHIFT PARA OBTENER LA REPRESENTACION BINARIA
              digitalWrite (pinout[j],HIGH); // PASO SALIDA A NIVEL LOGICO ALTO 
              }else {
                digitalWrite (pinout[j],LOW); //PASO SALIDA A NIVEL LOGICO BAJO
            	} //CIERRO IF 2 //CIERRO IF 1
           estadoPulsadorAntes = estadoPulsador;
           estadoPulsador=digitalRead(BUTTON_START);
//          }else{
//            digitalWrite(ZERO_TO_HERO,LOW);
//            i=0;
//            j=0;
//          }
        }// CIERRO FOR 1	
    	delay (BASE_MILLI_SECONDS); //DELAY DE 1 SEGUNDO
	 } // CIERRO FOR 2
  }//CIERRO WHILE   
}//CIERRO VOID