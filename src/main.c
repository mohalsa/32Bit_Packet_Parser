// Includes
#include "stm32f1xx.h"
#include <stdint.h>
#include "clocks.h"
#include "gpios.h"

// Prototypes
void delay(uint32_t delay);


int main(void)
{

    //pinMode(PIN13, GP_OUT_PP_2_MHZ);

    // Set PC13 MODE as Output @ 50Mhz (max). 
    GPIOC->CRH |= GPIO_CRH_MODE13_Msk;  
    // Setting Configuration for Pin PC13 CNF[1:0]
    GPIOC->CRH &= ~(GPIO_CRH_CNF13_Msk);

    while(1)
    {
        GPIOC->ODR ^= GPIO_ODR_ODR13_Msk;
        delay(50000);
        
        GPIOC->ODR ^= GPIO_ODR_ODR13_Msk;
        delay(50000);
    }
}


void delay(uint32_t delay)
{
    for(uint32_t volatile i = 0; i < delay; i++)    // Volatile is used so no optimization is done to this variable "i"
    {
        // Loop doing nothing!
    }
}