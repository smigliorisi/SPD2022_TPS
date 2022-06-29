#include <Keypad.h>
#include<LiquidCrystal.h>
#define BOTON_M1 1
#define BOTON_M2 2


LiquidCrystal pantalla(2,3,4,5,6,7);

const byte ROWS = 4;
const byte COLS = 4;
char key; 
char numero[7];
int indice=0;
int result;
int operacion;
int num1;
int num2;
int flag=0;
int flagPantalla = 0;
char num [7]={0,0,0,0,0,0,0};
int negativoAhora = 1;
int negativoAntes = 0;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'N','0','=','/'}
};

byte rowPins[ROWS] = { 8,  7,  6, 5 }; 
byte colPins[COLS] = { 12, 11, 10, 9 }; 
 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void initNumero()
{
  numero[0]=' ';
  numero[1]=0;
  numero[2]=0;
  numero[3]=0;
  numero[4]=0;
  numero[5]=0;
  numero[6]=0;
}

void nroNegativo()
{
  if(negativoAhora == 1)
  {
    numero[6] = numero[5];
    numero[5] = numero[4];
    numero[4] = numero[3];
    numero[3] = numero[2];
    numero[2] = numero[1];
    numero[1] = numero[0];
    numero[0] = '-';
    indice++;
    
   }
   else
   {
    
    numero[0] = numero[1];
    numero[1] = numero[2];
    numero[2] = numero[3];
    numero[3] = numero[4];
    numero[4] = numero[5];
    numero[5] = numero[6];
     indice--;
   }
  
  
}
void imprimirPantalla()
{	
   pantalla.clear();
 	if(flagPantalla == 1)
    {
      pantalla.setCursor(0,0);
        pantalla.print(num);
      pantalla.print(numero); 
    }
  	else
    {
      
      pantalla.setCursor(0,0);
      pantalla.print(numero);
    }
}
  
void cargarNro()
{
  if(key != 'N')
  {
  	numero[indice] = key;
  	indice++;
  }
}

void guardarNro()
{	
   if(flag==1)
    {
      num2 = atol(numero);
    }
    else
    {
      num1 = atol(numero);
      strcpy(num,numero);
    }

    flag = 0;
  
}



void resultado(int oper)
{ 
  switch(oper){
	case 1:
  	pantalla.setCursor(0,1);
	pantalla.print(num1+num2);
    break;
                   
    case 2:
  	pantalla.setCursor(0,1);
	pantalla.print(num1-num2);
    break;
                  
    case 3:
 	 pantalla.setCursor(0,1);
	pantalla.print(num1*num2);
    break;
                   
    case 4:
  	pantalla.setCursor(0,1);
	pantalla.print(num1/num2);
    break;
    }
}

void limpiador()
{
  indice=0;
 result =0;
 operacion = 0;
 num1=0;
 num2=0;
  flag=0;
  
}

void limpiaPantalla()
{
  if(key == '+')
  {
    pantalla.clear();
  }
}


void setup()
{
  
  pantalla.begin(16,2);

  Serial.begin(9600);
}

void loop()
{ 
  
  key  = kpd.getKey();
  
 	if(key)
    {	   
        
      cargarNro();
      imprimirPantalla();
      if(key == 'N')
      {
        nroNegativo();
       	negativoAhora = !negativoAhora;
        
        imprimirPantalla();
      }
      if(key == '+' || key == '-' ||key == '*' ||
         key == '/'|| key== '=')
      {
        guardarNro();
        initNumero();
        indice=0;
        flag=1;
        flagPantalla = 1;
        negativoAhora = 1;
        
        switch(key){
          case '+':
          operacion=1;
          
          break;
          
          case '-':
          operacion=2;
          break;
          
          case '*':
          operacion=3;
          break;
          
          case '/':
          operacion=4;
          break;
        }
        
       	if(key== '=')
        {
         resultado(operacion);
         limpiador();
         
         limpiaPantalla();	
        }
        
        Serial.println(num1);
        Serial.println(num2);
     
      }
     
      
    }
}

