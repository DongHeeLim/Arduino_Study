#include "NDelayFunc.h"


const int blink_LED = 13;
unsigned int on_off = 0;

const int fading_LED = 10;
unsigned int t_high = 0;

const int twoAone_LED = 9;



void blink(){

  on_off++;
  if(on_off > 1) on_off = 0;
  digitalWrite(blink_LED, on_off);
}

void fading(){
  t_high++;
  if(t_high > 255) t_high = 0;
  analogWrite(fading_LED, t_high);  
}

void twoAone(){

  on_off++;
  if(on_off> 1) on_off = 0; 
  
  if(on_off == 1)
  {
    digitalWrite(twoAone_LED,HIGH);
    delay(200);
    digitalWrite(twoAone_LED,LOW);
    delay(200);
    digitalWrite(twoAone_LED,HIGH);
    delay(200);
    digitalWrite(twoAone_LED,LOW);
    delay(200);
  }    
}

NDelayFunc nDelayBlink(500, blink);
NDelayFunc nDelayFading(15, fading);

NDelayFunc nDelaytwoAone(500, twoAone);

void setup(){
  pinMode(blink_LED, OUTPUT);  
}

void loop(){
  
//  nDelayBlink.run();
//  nDelayFading.run();
  nDelaytwoAone.run();
}
