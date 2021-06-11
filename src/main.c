// Includes
#include "stm32f1xx.h"
#include <stdint.h>
#include "FRAMEWORK.h"

#define DELAY_T (50000)         // Psuedo Delay function

// Prototypes
void delay(uint32_t delay);


int main(void)
{
    pinMode (PB9, INPUT_PULLUP);
    pinMode (PC13_LED, GP_OUT_PP_50_MHZ);
  


    while(1)
    {
        digitalWrite(PC13_LED, HIGH);
        delay (DELAY_T);
        digitalWrite(PC13_LED, LOW);
        delay (DELAY_T);
    }
        
}


void delay(uint32_t delay)
{
    for(uint32_t volatile i = 0; i < delay; i++) {/*Empty loop!*/}
}