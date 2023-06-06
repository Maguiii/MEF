#include <Arduino.h>
#include <TimerOne.h>

/*Este codigo es la Maquina de estados finitos que se va a usar para los pulsadores
  En este caso se esta implementando con un pulsador y un led 
  A este codigo le falta correccion 
*/
#define FALSE 0
#define TRUE 1
#define puls 10
#define led 9

volatile int t = 0;
volatile int estado = 1;
volatile bool flagRetencion = FALSE;
volatile bool flagPulso = FALSE;

void contando();

void state1(){
  if(digitalRead(puls) == HIGH)
    estado = 1;

  if(digitalRead(puls) == LOW){
    t = 0;
    estado = 2;
  }
}
void state2(){
  if(!flagRetencion)//== FALSE
    estado = 2;
  if(flagRetencion)//== TRUE
    estado = 3;
}
void state3(){
  if(digitalRead(puls) == HIGH){
    flagPulso = FALSE;
    estado = 1;
  }
  if(digitalRead(puls) == LOW){
    flagPulso = TRUE;
    estado = 1;
  }
}


void setup(){
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
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
}

void contando(){
  t++;
  
  if(t >= 100)
    flagRetencion = TRUE;
  else
    flagRetencion = FALSE;
}