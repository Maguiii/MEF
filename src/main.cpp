#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>


/*Este codigo es la Maquina de estados finitos que se va a usar para los pulsadores
  En este caso se esta implementando con un pulsador que incrementa una variable y la muestra en un lcd
  Este codigo esta probado y funciona
  A este codigo le falta correccion de un profesor
*/
#define FALSE 0
#define TRUE 1

#define puls 10
#define led 9

LiquidCrystal_I2C lcd(0x3F, 16, 2);

volatile int t = 0;
volatile int estado = 1;
volatile bool flagRetencion = FALSE;
volatile bool flagPulso = FALSE;
volatile int contador = 0;

void contando();

void state1(){
  flagPulso = FALSE;

  if(digitalRead(puls) == HIGH)
    estado = 1;

  if(digitalRead(puls) == LOW){
    t = 0;
    estado = 2;
  }
}
void state2(){
  if(!flagRetencion == FALSE)
    estado = 2;
  if(flagRetencion == TRUE)
    estado = 3;
}
void state3(){
  flagPulso = TRUE;
  estado = 1;
}


void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Esto funciona");
  delay(1000);
  lcd.clear();

  pinMode(puls, INPUT);

  Timer1.initialize(1000);//1ms
  Timer1.attachInterrupt(contando);
}

void loop(){
  switch(estado){
    case 1: state1(); break;
    case 2: state2(); break;
    case 3: state3(); break;
  }
  if(flagPulso == TRUE){
    contador++;
  }
  lcd.setCursor(0,0);
  lcd.print("Cant:");
  lcd.print(contador);
}

void contando(){
  t++;
  
  if(t >= 300)
    flagRetencion = TRUE;
  else
    flagRetencion = FALSE;
}