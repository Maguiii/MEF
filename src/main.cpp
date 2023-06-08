#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>

/*Retencion de pulsadores implementado como una maquina de estados finitos
  En este caso se esta implementando con un pulsador que incrementa una variable y la muestra en un lcd
  Este codigo esta probado y funciona
  Tambien esta corregido
*/
#define FALSE 0
#define TRUE 1

#define puls 10

LiquidCrystal_I2C lcd(0x3F, 16, 2);

volatile int t = 0;
volatile int estadoRetencion = 0; 

volatile bool flagRetencion = FALSE;
volatile bool flagPulso = FALSE;

volatile int contador = 0;

void tiempo();

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Esto funciona");
  delay(1000);
  lcd.clear();

  pinMode(puls, INPUT);

  Timer1.initialize(1000);//1ms
  Timer1.attachInterrupt(tiempo);
}

void loop(){
  switch(estadoRetencion){
    case 1:
      flagPulso = FALSE;

      if(digitalRead(puls) == HIGH)
        estadoRetencion = 1;

      if(digitalRead(puls) == LOW){
        t = 0;
        estadoRetencion = 2;
      }
    break;
    case 2:
      if(flagRetencion == FALSE)
        estadoRetencion = 2;
      if(flagRetencion == TRUE)
        estadoRetencion = 3;
    break;
    case 3: 
      if(digitalRead(puls) == LOW){
        flagPulso = TRUE;
        estadoRetencion = 1;
      }
      else{
        flagPulso = FALSE;
        estadoRetencion = 1;
      }
    break;
  }
  
  if(flagPulso == TRUE){
    contador++;
  }
  lcd.setCursor(0,0);
  lcd.print("Cant:");
  lcd.print(contador);
}

void tiempo(){
  t++;
  
  if(t >= 100)
    flagRetencion = TRUE;
  else
    flagRetencion = FALSE;
}