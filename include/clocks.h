#ifndef CLOCKS_H_
#define CLOCKS_H_
#include <stdint.h>


// Variables Definitions
uint32_t* const pRCC_APB2_ENR   =   (uint32_t*)(0x40021000 + 0x18);   // RCC_APB2 Bus Memory Address
uint32_t* const pPORT_CRH      =   (uint32_t*)(0x40011000 + 0x04);   // Port C Control Register High (Pin 8 to pin 15)
uint32_t* const pPORTC_CRL      =   (uint32_t*)(0x40011000 + 0x00);   // Port C Control Register Low  (Pin 0 to pin 7)
uint32_t* const pODR_C          =   (uint32_t*)(0x40011000 + 0x0C);   // Port C Output Data Register
uint32_t* const pIDR_C          =   (uint32_t*)(0x40011000 + 0x08);

// PORTS PINS
#define PC13    (2)                      //2 = PC13's MCU's Pin

// RCC Addresses
#define APB2    (0x40021000)

// GPIOx Addresses
#define GPIO_A
#define GPIO_B
#define GPIO_C  (0x40011000)
#define GPIO_D

// PIN REGISTER CNF & MODE START BIT  0b0000 = CNF[1:0] Mode[1:0] = 0b(CNF1)(CNNF0)(MODE1)(MODE0)
#define P8                       (0)

// OUTPUT MODES and CONFIGURATIONS
#define GP_OUT_PP_2_MHZ          (1)     //General purpose output Push-Pull
#define GP_OUT_PP_10_MHZ         (2)     //General purpose output Push-Pull
#define GP_OUT_PP_50_MHZ         (3)     //General purpose output Push-Pull

#define GP_OUT_OD_2_MHZ          (4)     //General purpose output Open-Drain
#define GP_OUT_OD_10_MHZ         (5)     //General purpose output Open-Drain
#define GP_OUT_OD_50_MHZ         (6)     //General purpose output Open-Drain

#define ALT_OUT_PP_2_MHZ         (7)     //Alternate Function Push Pull
#define ALT_OUT_PP_10_MHZ        (8)     //Alternate Function Push Pull
#define ALT_OUT_PP_50_MHZ        (9)     //Alternate Function Push Pull

#define ALT_OUT_OD_2_MHZ         (10)    //Alternate Function Open Drain
#define ALT_OUT_OD_10_MHZ        (11)    //Alternate Function Open Drain
#define ALT_OUT_OD_50_MHZ        (12)    //Alternate Function Open Drain

// INPUT MODES CONFIGURATIONS
#define ANALOG_IN                (13)
#define FLOATING_IN              (14)
#define INPUT_PULLUP             (15)
#define INPUT_PULLDOWN           (16)


void pinMode(uint8_t pin, uint8_t mode)
{
    uint32_t*  pPORT_CRH ;
    uint32_t*  pPORT_CRL ;
    uint32_t*  pODR      ;
    uint32_t*  pIDR      ;

    if (pin >= 2 && pin <= 4)   // if a pin from port C is selected
    {
        *pRCC_APB2_ENR  |= (1<<4);              // Enable Clock on port C
        pPORT_CRH   =   (uint32_t*)(0x40011000 + 0x04);   // Port C Control Register High (Pin 8 to pin 15)
        pPORT_CRL   =   (uint32_t*)(0x40011000 + 0x00);   // Port C Control Register Low  (Pin 0 to pin 7)
        pODR_C      =   (uint32_t*)(0x40011000 + 0x0C);   // Port C Output Data Register
        pIDR_C      =   (uint32_t*)(0x40011000 + 0x08);   // Port C input Data Register
    }

    switch (pin) // Pin = mcu masked pin pc13 = mcu pin 2
    { 
    case 2:                                     // 2 = PC13's MCU's Pin
        #define PIN_REG_START (20)              // Pin13 is at CRH register starting at bit(20)
        if (mode >=1 && mode <= 16)             // For pin modes and configs (1 to 12 options)
        {
            switch (mode)
            {
            // GP Push-Pull Configurations
            case 1: // OUTPUT GEN PURP Push-Pull 2 MHZ
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x2 << PIN_REG_START);
                break;
            
            case 2: // OUTPUT GEN PURP Push-Pull 10 MHZ
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x1 << PIN_REG_START);
                break;
            
            case 3: // OUTPUT GEN PURP Push-Pull 50 MHZ
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |=  (0x3 << PIN_REG_START);
                break;

            // GP Open-Drain Configurations
            case 4: // OUTPUT GEN PURP Open-Drain 2 MHZ (0b0110 = 0x6)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x6 << PIN_REG_START);
                break;
            
            case 5: // OUTPUT GEN PURP Open-Drain 10 MHZ (0b0101 = 0x5)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x5 << PIN_REG_START);
                break;
            
            case 6: // OUTPUT GEN PURP Open-Drain 50 MHZ (0b0111 = 0x7)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |=  (0x7 << PIN_REG_START);
                break;  


            // Alternate Function Configurations: Push-Pull (0b10 = 0x2)
            case 7: // Alt Func Push-Pull 2 MHZ
            *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
            *pPORT_CRH |= (0xa << PIN_REG_START);     // 0b1010 = 0xa
            break;
            
            case 8: // Alt Func Push-Pull 10 MHZ
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x9 << PIN_REG_START);     // 0b1001 = 0x9
                break;
            
            case 9: // Alt Func Push-Pull 50 MHZ
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |=  (0xb << PIN_REG_START);    // 0b1011 = 0xb
                break;

            /* Alternate Function Configurations: Open-Drain (0b11 = 0x3) */
            
            case 10: // Alt Func Open-Drain 2 MHZ (0b1110 = 0x6)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0xe << PIN_REG_START);     // 0b1110 = 0xe = 14
                break;
            
            case 11: // Alt Func Open-Drain 10 MHZ (0b1101 = 0x5)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x13 << PIN_REG_START);     // 0b1101 = 0x13
                break;
            
            case 12: // Alt Func Open-Drain 50 MHZ (0b1111 = 0x7)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |=  (0xf << PIN_REG_START);    // 0b1111 = oxf
                break;  

            // Input Modes Configurations

            case 13: // Input Analog Mode
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x0 << PIN_REG_START);     // 0b 0000

            case 14: // Input Floating Mode (reset state)
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x4 << PIN_REG_START);     // 0b0100

            case 15: // Input Pull-Up
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x8 << PIN_REG_START);     // 0b1000
                //ODR 0

            case 16: // Input Pull-Up
                *pPORT_CRH &= ~(0xf << PIN_REG_START);    // Reset all 4 bits of pin 13
                *pPORT_CRH |= (0x8 << PIN_REG_START);     // 0b1000
                //ODR 1

            default:
                break;
            } // End 2nd Switch
        } //End if (pins output modes)
        else
        {
            // Error Code emplementation for selecting an incorrect option for modes and configs!
        }

        // For input modes
        if (mode == 1)
        {
            //input code!
        }  
        else
        {
            //ERROR INDICATOR not in not out!
        }
        break;
    
    default:
        break;
    } // End main switch (pin selector)

}

#endif