#include "ADC.h"
#include "dio.h"
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>


void init();

int main(){
  init();
  
  //Temperature limits
  float temp_min = 18.0;
  float temp_max = 45.0;  
  
  while(1){
    int ButtonsInput = ADC_Read(0); // ADC value of the Buttons Input Pin
    float tempAnalog = ADC_Read(1); // ADC value of the LM35 Temperature sensor Pin
    _delay_ms(100);

    float temp_cel = tempAnalog/2.048;
    char temp_string[5];
    itoa(temp_cel, temp_string, 10);
        
    LCD_String_xy(0,0,"Temp: ");
    LCD_String_xy(0,6, temp_string);
    LCD_String_xy(0,9, "C");

    if(ButtonsInput < 100 ){ // Button 1 action
      temp_min-=1;
      _delay_ms(100);
    }
    else if(ButtonsInput < 600){ //Button 2 action
      temp_min+=1;
      _delay_ms(100);
    }
    else if(ButtonsInput < 700){ //Button 3 action
      temp_max-=1;
      _delay_ms(100);
    }
    else if(ButtonsInput < 900){ //Button 4 action
      temp_max+=1;
      _delay_ms(100);
    } 
    else { // No Button action
      
    }

    char temp_min_string[5];
    itoa(temp_min, temp_min_string, 10);

    LCD_String_xy(1,0, "Min: ");
    LCD_String_xy(1,5, temp_min_string);

    char temp_max_string[5];
    itoa(temp_max, temp_max_string, 10);

    LCD_String_xy(1,8, "Max: ");
    LCD_String_xy(1,13, temp_max_string);

    if(temp_cel > temp_max || temp_cel < temp_min){
      DIO_SetPinState('d', 2, 'h');
    } else{
      DIO_SetPinState('d', 2, 'l');
    }

    _delay_ms(200);
  }

  return 0;
}

void init(){
  Serial.begin(9600);
  // Initalizing ADC and DIO
  LCD_Init();
  
  ADC_Init();
  DIO_init();   
}