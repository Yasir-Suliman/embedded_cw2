#include "ADC.h"
#include "dio.h"
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>


void init();

int main(){
  init();
  
  //Temperature limits
  float temp_min = 20.0;
  float temp_max = 30.0;  
  
  while(1){
    int ButtonsInput = ADC_Read(0); // ADC value of the Buttons Input Pin
    float tempAnalog = ADC_Read(1); // ADC value of the LM35 Temperature sensor Pin
    _delay_ms(100);

    float temp_cel = tempAnalog/2.048; // converting sensor reading to celsius
    char temp_string[5]; // empty string
    itoa(temp_cel, temp_string, 10); // convert celsius value from float to string

    // printing the upper row on the lcd which displays sensor reading in celsius
    LCD_String_xy(0,0,"Temp: ");
    LCD_String_xy(0,6, temp_string);
    LCD_String_xy(0,9, "C");

    if(ButtonsInput < 100 ){ // Action when Button 1 pressed
      temp_min-=1; // decrement lower temp limit by 1
      _delay_ms(100);
    }
    else if(ButtonsInput < 600){ //Action when Button 2 pressed
      temp_min+=1; // increment lower temp limit by
      _delay_ms(100);
    }
    else if(ButtonsInput < 700){ //Action when Button 3 pressed
      temp_max-=1; // decrement upper temp limit by 1
      _delay_ms(100);
    }
    else if(ButtonsInput < 900){ //Action when button 4 pressed
      temp_max+=1; // increment upper temp limit by 1
      _delay_ms(100);
    } 
    else { // No Button action
      
    }
        
    // converting lower temp limit from float to string and displaying on the lower row of the lcd
    char temp_min_string[5];
    itoa(temp_min, temp_min_string, 10);

    LCD_String_xy(1,0, "Min: ");
    LCD_String_xy(1,5, temp_min_string);

    // converting upper temp limit from float to string and displaying on the lower row of the lcd
    char temp_max_string[5];
    itoa(temp_max, temp_max_string, 10);

    LCD_String_xy(1,8, "Max: ");
    LCD_String_xy(1,13, temp_max_string);

    // checking if sensor reading exceeds upper limit or drops below lower limit
    if(temp_cel > temp_max || temp_cel < temp_min){
      DIO_SetPinState('d', 2, 'h'); // turn led on if TRUE
    } else{
      DIO_SetPinState('d', 2, 'l'); // turn led off if FALSE
    }

    _delay_ms(200);
  }

  return 0;
}

void init(){
  LCD_Init(); // initialise LCD
  ADC_Init(); // initialise ADC

  //  Initialise DIO and setting pins used to Input or Output
  DIO_init();   
}