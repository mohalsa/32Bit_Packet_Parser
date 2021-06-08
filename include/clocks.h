#ifndef CLOCKS_H_
#define CLOCKS_H_
#include <stdint.h>


// Variables Definitions
uint32_t* const pRCC_APB2_ENR   =   (uint32_t*)(0x40021000 + 0x18);   // RCC_APB2 Bus Memory Address
uint32_t* const pPORTC_CRH       =   (uint32_t*)(0x40011000 + 0x04);   // Port C Control Register High (Pin 8 to pin 15)
uint32_t* const pPORTC_CRL      =   (uint32_t*)(0x40011000 + 0x00);   // Port C Control Register Low  (Pin 0 to pin 7)
uint32_t* const pODR_C          =   (uint32_t*)(0x40011000 + 0x0C);   // Port C Output Data Register
uint32_t* const pIDR_C          =   (uint32_t*)(0x40011000 + 0x08);

uint32_t*   pPORT_Ctr_Reg ;
uint32_t*   pPORT_CRH     ;
uint32_t*   pPORT_CRL     ;
uint32_t*   pODR          ;
uint32_t*   pIDR          ;
uint8_t     pinNum        ;                                // Use for direct pin-bit representation


//Keywords
#define HIGH    (1)
#define LOW     (0)

// PORTS and PINS and thier corresponding MCU Pin Number
#define PC13    (2)             // Corresponding MCU Pin Number
#define PC14    (3)             // Corresponding MCU Pin Number
#define PC15    (4)             // Corresponding MCU Pin Number
#define PB0     (18)            // Corresponding MCU Pin Number
#define PB1     (19)            // Corresponding MCU Pin Number
#define PB3     (39)            // Corresponding MCU Pin Number
#define PB4     (40)            // Corresponding MCU Pin Number
#define PB5     (41)            // Corresponding MCU Pin Number
#define PB6     (42)            // Corresponding MCU Pin Number
#define PB7     (43)            // Corresponding MCU Pin Number
#define PB8     (45)            // Corresponding MCU Pin Number
#define PB9     (46)            // Corresponding MCU Pin Number
#define PB10    (21)            // Corresponding MCU Pin Number
#define PB11    (22)            // Corresponding MCU Pin Number
#define PB12    (25)            // Corresponding MCU Pin Number
#define PB13    (26)            // Corresponding MCU Pin Number
#define PB14    (27)            // Corresponding MCU Pin Number
#define PB15    (28)            // Corresponding MCU Pin Number

// RCC Addresses
#define APB2    (0x40021000)

// GPIOx Addresses
#define GPIO_A  (0x40010800)
#define GPIO_B  (0x40010C00)
#define GPIO_C  (0x40011000)
#define GPIO_D  (0x40011400)


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

// Function prototypes
uint8_t get_pin_bit(uint8_t pinNum);

void pinMode(uint8_t pin, uint8_t mode)
{
    // Global variables to pinMode function:
    uint8_t volatile pinBit = 0;

    // For port "C"
    if (pin >= 2 && pin <= 4)   // if a pin from port C is selected
    {
        *pRCC_APB2_ENR  |=  (1<<4);                       // Enable Clock on port C
        pPORT_CRH       =   (uint32_t*)(GPIO_C + 0x04);   // Port C Control Register High (Pin 8 to pin 15)
        pPORT_CRL       =   (uint32_t*)(GPIO_C + 0x00);   // Port C Control Register Low  (Pin 0 to pin 7)
        pODR            =   (uint32_t*)(GPIO_C + 0x0C);   // Port C Output Data Register
        pIDR            =   (uint32_t*)(GPIO_C + 0x08);   // Port C input Data Register
        pinNum          =   pin + 11;                     // Example, if pin PC13 is selected, coresponding MCU pin number = 2, therefore 2 + 11 = 13, 13 can be used for pin-bit direct mapping in some registers i.e IDR and ODR
        pPORT_Ctr_Reg   =   pPORT_CRH;
        pinBit          =   get_pin_bit(pinNum);

    }
    // For port "B"
    if (pin == 19 || (pin >= 39 && pin <= 46) || (pin >= 25 && pin <= 28) || (pin == 21) || (pin == 22))
    {
        *pRCC_APB2_ENR  |=  (1<<3);                       // Enable Clock on port B
        pPORT_CRH       =   (uint32_t*)(GPIO_B + 0x04);   // Port B Control Register High (Pin 8 to pin 15)
        pPORT_CRL       =   (uint32_t*)(GPIO_B + 0x00);   // Port B Control Register Low  (Pin 0 to pin 7)
        pODR            =   (uint32_t*)(GPIO_B + 0x0C);   // Port B Output Data Register
        pIDR            =   (uint32_t*)(GPIO_B + 0x08);   // Port B input Data Register        
        if (pin == 19 || pin == 18) {pinNum = pin - 18; pPORT_Ctr_Reg = pPORT_CRL;}
        if (pin == 45 || pin == 46) {pinNum = pin - 37; pPORT_Ctr_Reg = pPORT_CRH;}    
        if (pin >= 39 && pin <= 43) {pinNum = pin - 36; pPORT_Ctr_Reg = pPORT_CRL;}
        if (pin == 22 || pin == 21) {pinNum = pin - 11; pPORT_Ctr_Reg = pPORT_CRH;}
        if (pin >= 25 && pin <= 28) {pinNum = pin - 13; pPORT_Ctr_Reg = pPORT_CRH;}
        pinBit          =   get_pin_bit(pinNum);
 
    }

    switch (mode)
    {
    // GP Push-Pull Configurations
    case 1: // OUTPUT GEN PURP Push-Pull 2 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x2 << pinBit);
        break;
    
    case 2: // OUTPUT GEN PURP Push-Pull 10 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x1 << pinBit);
        break;
    
    case 3: // OUTPUT GEN PURP Push-Pull 50 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |=  (0x3 << pinBit);
        break;

    // GP Open-Drain Configurations
    case 4: // OUTPUT GEN PURP Open-Drain 2 MHZ (0b0110 = 0x6)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x6 << pinBit);
        break;
    
    case 5: // OUTPUT GEN PURP Open-Drain 10 MHZ (0b0101 = 0x5)
        *pPORT_Ctr_Reg &= ~(0xf <<pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x5 << pinBit);
        break;
    
    case 6: // OUTPUT GEN PURP Open-Drain 50 MHZ (0b0111 = 0x7)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |=  (0x7 << pinBit);
        break;  


    // Alternate Function Configurations: Push-Pull (0b10 = 0x2)
    case 7: // Alt Func Push-Pull 2 MHZ
    *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
    *pPORT_Ctr_Reg |= (0xa << pinBit);     // 0b1010 = 0xa
    break;
    
    case 8: // Alt Func Push-Pull 10 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x9 << pinBit);     // 0b1001 = 0x9
        break;
    
    case 9: // Alt Func Push-Pull 50 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |=  (0xb << pinBit);    // 0b1011 = 0xb
        break;

    /* Alternate Function Configurations: Open-Drain (0b11 = 0x3) */
    
    case 10: // Alt Func Open-Drain 2 MHZ (0b1110 = 0x6)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0xe << pinBit);     // 0b1110 = 0xe = 14
        break;
    
    case 11: // Alt Func Open-Drain 10 MHZ (0b1101 = 0x5)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x13 << pinBit);     // 0b1101 = 0x13
        break;
    
    case 12: // Alt Func Open-Drain 50 MHZ (0b1111 = 0x7)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |=  (0xf << pinBit);    // 0b1111 = oxf
        break;  

    // Input Modes Configurations

    case 13: // Input Analog Mode
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x0 << pinBit);     // 0b 0000

    case 14: // Input Floating Mode (reset state)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x4 << pinBit);     // 0b0100

    case 15: // Input Pull-Up
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x8 << pinBit);     // 0b1000
        *pODR &= ~(1<<pinNum);

    case 16: // Input Pull-Up
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);    // Reset all 4 bits of pin 13
        *pPORT_Ctr_Reg |= (0x8 << pinBit);     // 0b1000
        *pODR |= (1<<pinNum);

    default:
        break;
    } // End  Switch
} // End pinModes function


int digitalRead(int pin)
{
    {
        // Make sure the selected pin is in input mode (pull up or pull down not analog not floating)
    }

    // For port "B"
    if (pin == 19 || (pin >= 39 && pin <= 46) || (pin >= 25 && pin <= 28) || (pin == 21) || (pin == 22))
    {
        //*pRCC_APB2_ENR  |=  (1<<3);                       // Enable Clock on port B
        //pPORT_CRH       =   (uint32_t*)(GPIO_B + 0x04);   // Port B Control Register High (Pin 8 to pin 15)
        //pPORT_CRL       =   (uint32_t*)(GPIO_B + 0x00);   // Port B Control Register Low  (Pin 0 to pin 7)
        //pODR            =   (uint32_t*)(GPIO_B + 0x0C);   // Port B Output Data Register
        pIDR              =   (uint32_t*)(GPIO_B + 0x08);   // Port B input Data Register        
        if (pin == 19 || pin == 18) {pinNum = pin - 18; pPORT_Ctr_Reg = pPORT_CRL;}
        if (pin == 45 || pin == 46) {pinNum = pin - 37; pPORT_Ctr_Reg = pPORT_CRH;}    
        if (pin >= 39 && pin <= 43) {pinNum = pin - 36; pPORT_Ctr_Reg = pPORT_CRL;}
        if (pin == 22 || pin == 21) {pinNum = pin - 11; pPORT_Ctr_Reg = pPORT_CRH;}
        if (pin >= 25 && pin <= 28) {pinNum = pin - 13; pPORT_Ctr_Reg = pPORT_CRH;} 
    }
    
    
    
    uint16_t input_status = (uint16_t)(*pIDR & (1<<pinNum));
    if (input_status)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


void digitalWrite(uint8_t pin, uint8_t output)
{
    // For port "B"
    if (pin == 19 || (pin >= 39 && pin <= 46) || (pin >= 25 && pin <= 28) || (pin == 21) || (pin == 22))
    {
        *pRCC_APB2_ENR  |=  (1<<3);                       // Enable Clock on port B
        pODR            =   (uint32_t*)(GPIO_B + 0x0C);   // Port B Output Data Register
        if (pin == 19 || pin == 18) {pinNum = pin - 18;}
        if (pin == 45 || pin == 46) {pinNum = pin - 37;}    
        if (pin >= 39 && pin <= 43) {pinNum = pin - 36;}
        if (pin == 22 || pin == 21) {pinNum = pin - 11;}
        if (pin >= 25 && pin <= 28) {pinNum = pin - 13;} 
    }
    
    // For port "C"
    if (pin >= 2 && pin <= 4)   // if a pin from port C is selected
    {
        *pRCC_APB2_ENR  |=  (1<<4);                       // Enable Clock on port C
        pODR            =   (uint32_t*)(GPIO_C + 0x0C);   // Port C Output Data Register
        pinNum          =   pin + 11;                     // Example, if pin PC13 is selected, coresponding MCU pin number = 2, therefore 2 + 11 = 13, 13 can be used for pin-bit direct mapping in some registers i.e IDR and ODR
    }

    if (output == 1)
    {
        *pODR |= (1<<pinNum);       // Set the  Pin's corresponding Output data register
    }
    else
    {
        *pODR &= ~(1<<pinNum);      // Clear the  Pin's corresponding Output data register
    }
}

void analogRead()
{
    //todo
}

uint8_t get_pin_bit(uint8_t pinNum)
{
    if(pinNum == 0)  return 0 ;
    if(pinNum == 1)  return 4 ;
    if(pinNum == 2)  return 8 ;
    if(pinNum == 3)  return 12;
    if(pinNum == 4)  return 16;
    if(pinNum == 5)  return 20;
    if(pinNum == 6)  return 24;
    if(pinNum == 7)  return 28;
    if(pinNum == 8)  return 0;
    if(pinNum == 9)  return 4;
    if(pinNum == 10) return 8;
    if(pinNum == 11) return 12;
    if(pinNum == 12) return 16;
    if(pinNum == 13) return 20;
    if(pinNum == 14) return 24;
    if(pinNum == 15) return 28;
    return 0;
}
#endif