#include "ADC.h"
#include "dio.h"
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>

void init();

int main(){
  init();
  float temp_min = 18.0;
  float temp_max = 45.0;  
  while(1){
    int ButtonsInput = ADC_Read(0);
    int temp = ADC_Read(1);
    float temp_cel = (temp*500.0)/1024.0;
    Serial.print("Current: ");
    Serial.println(temp_cel);
    Serial.print("Limit: ");
    Serial.println(temp_max);

    if(ButtonsInput < 100 ){ // Button 1 action
      temp_max-=1;
      _delay_ms(100);
    }
    else if(ButtonsInput < 600){ //Button 2 action
      temp_max+=1;
      _delay_ms(100);
    }
    else if(ButtonsInput < 700){ //Button 3 action
      Serial.println("Button 3");
    }
    else if(ButtonsInput < 900){ //Button 4 action
      Serial.println("Button 4");
    } 
    else { // No Button action
      // Serial.println("No Button");
    }

    if(temp_cel > temp_max){
      DIO_SetPinState('d', 7, 'h');
    } else{
      DIO_SetPinState('d', 7, 'l');      
    }

    _delay_ms(100);
  }

  return 0;
}

void init(){
  Serial.begin(9600);
  ADC_Init();
  DIO_init();   
}