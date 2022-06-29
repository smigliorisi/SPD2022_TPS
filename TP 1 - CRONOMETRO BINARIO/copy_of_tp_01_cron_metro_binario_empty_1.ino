/*Trabajo Práctico 1: Cronómetro Binario
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

#define ZERO_TO_HERO 0          //? To start the counter from 0
#define BUTTON_START 3
#define BUTTON_RESET 2
#define FIRST_LED 4             //? First pin of the leds
#define LAST_LED 13             //? Last pin of the leds
#define BASE_MILLI_SECONDS 1000 //? Secods expresed in miliseconds
#define MAX_SECONDS 1023        //! Max amount of secods to show
#define TAM_BINARIO 10
//--- End Defines ---//
void setPins(){                 //seteo de pins
  
  for(int i=FIRST_LED; i<=LAST_LED; i++){
    pinMode(i, OUTPUT);
  }
}

void setButtons(){              //seteo de botones
  
  pinMode(BUTTON_RESET, INPUT);
  pinMode(BUTTON_START, INPUT);
}

void setup(){
  setPins();
  setButtons();
  Serial.begin(9600);
}

//Variables
short contador = ZERO_TO_HERO;              
int arrayBinario[TAM_BINARIO];               //Un array con los digitos del numero del contador en binario
unsigned long millisBefore = 0;
short botonReset = LOW;                        //Estado del boton antes de se clickeado
short banderaInicio = 0;                     //bandera para determinar si un boton ya fue clickeado

void decimalAbinario(int cont, int array[]){
    short numeroBin = 0;
	int ultimoIndice = TAM_BINARIO-1;
    
    
    while( cont > 0){                           // Arma cadena binaria en el array
        numeroBin = cont % 2;
        cont /= 2;
        array[ultimoIndice] = numeroBin;
        ultimoIndice--;
    }

    
    while(ultimoIndice >= 0){               // rellenar con 0 hacia la izquierda.
        array[ultimoIndice] = 0;
        ultimoIndice--;
    }
}


void imprimirCadena(){   //Imprime los numeros en binario
  
  	Serial.print("Binario ");
    for(int i = 0; i < TAM_BINARIO; i++){
        Serial.print(arrayBinario[i]);
    }
  	
  	Serial.print(" | Decimal ");
    Serial.print(contador);
    Serial.println("");
}


void turnLed(int arr[], int tam){                   //Enciende los led según el valor del digito
  for(int i = 0; i<tam; i++){
    digitalWrite(LAST_LED-i, arr[i]);
  }
}


void conteo(){                                              //Esta funcion realiza el conteo
  unsigned long millisNow = millis();
  	if(millisNow - millisBefore >= BASE_MILLI_SECONDS){
    decimalAbinario(contador, arrayBinario);
    imprimirCadena();
    turnLed(arrayBinario, TAM_BINARIO);
    contador++;
    millisBefore = millisNow;
  }
}


void iniciaCronometro()
{
 int botonInicio = digitalRead(BUTTON_START);
 
  if(banderaInicio == 1 && contador <= MAX_SECONDS)
  {
    conteo();  
  }
  
  if(botonInicio == HIGH && botonReset == LOW  &&
     banderaInicio == 0)
  {
    banderaInicio = 1;
    
  }else if(botonInicio == HIGH && botonReset == LOW &&    //Inicia y pausa el conteo
           banderaInicio == 1)
  {
    banderaInicio = 0;
  }
  
  botonReset = botonInicio;
}


void resetCronometro(){                            //Se reinicia el contador
  int botonInicio = digitalRead(BUTTON_RESET);
  if(botonInicio == HIGH && botonReset == LOW){
    contador = ZERO_TO_HERO;
  }
  botonInicio = botonReset;
}

void loop(){
  iniciaCronometro();
  resetCronometro();
  if(contador>MAX_SECONDS){
    contador = ZERO_TO_HERO;
  }
  delay(80);
}