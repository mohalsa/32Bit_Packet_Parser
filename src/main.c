// Includes
#include "stm32f1xx.h"
#include <stdint.h>
#include "clocks.h"
#include "gpios.h"

// Prototypes
void delay(uint32_t delay);


int main(void)
{
    pinMode (PB9, INPUT_PULLUP);
    pinMode (PC13, GP_OUT_PP_50_MHZ);

    while(1)
    {
        if(digitalRead(PB9))
        {
            digitalWrite(PC13, HIGH);
        }
        else
        {
            digitalWrite(PC13, LOW);
        }
        delay(10000);
    }
}


void delay(uint32_t delay)
{
    for(uint32_t volatile i = 0; i < delay; i++)    // Volatile is used so no optimization is done to this variable "i"
    {
        // Loop doing nothing!
    }
}