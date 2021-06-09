#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_
#include <stdint.h>


// Variables Definitions
uint32_t volatile *const pRCC_APB2_ENR   =   (uint32_t*)(0x40021000 + 0x18);   // RCC_APB2 Bus Memory Address
uint32_t volatile *const pPORTC_CRH      =   (uint32_t*)(0x40011000 + 0x04);   // Port C Control Register High (Pin 8 to pin 15)
uint32_t volatile *const pPORTC_CRL      =   (uint32_t*)(0x40011000 + 0x00);   // Port C Control Register Low  (Pin 0 to pin 7)
uint32_t volatile *const pODR_C          =   (uint32_t*)(0x40011000 + 0x0C);   // Port C Output Data Register
uint32_t const volatile *const pIDR_C    =   (uint32_t*)(0x40011000 + 0x08);

uint32_t volatile *pPORT_Ctr_Reg ;
uint32_t volatile *pPORT_CRH     ;
uint32_t volatile *pPORT_CRL     ;
uint32_t volatile *pODR          ;
uint32_t const volatile *pIDR    ;      // The data pointed-to by pIDR pointer is subjected to unexpected changes (volatile), but the programmer can't change the data present in the address (const)
uint8_t pinNum;                         // Use for direct pin-bit mapping

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
#define PB15    (28)            // Corresponding MCU Pin Number

#define PA0     (10)            // Corresponding MCU Pin Number
#define PA1     (11)            // Corresponding MCU Pin Number
#define PA2     (12)            // Corresponding MCU Pin Number
#define PA3     (13)            // Corresponding MCU Pin Number
#define PA4     (14)            // Corresponding MCU Pin Number
#define PA5     (15)            // Corresponding MCU Pin Number
#define PA6     (16)            // Corresponding MCU Pin Number
#define PA7     (17)            // Corresponding MCU Pin Number
#define PA8     (29)            // Corresponding MCU Pin Number
#define PA9     (30)            // Corresponding MCU Pin Number
#define PA10    (31)            // Corresponding MCU Pin Number
#define PA11    (32)            // Corresponding MCU Pin Number
#define PA12    (33)            // Corresponding MCU Pin Number
#define PA15    (38)            // Corresponding MCU Pin Number



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
    /* pinBit is the corresponding bit number for each pin's configuratin first bit in MODE-CNF in CRx register (x = high or low) */
    uint8_t volatile pinBit = 0;

    // Port "A" Initialization
    if ((pin >= 10 && pin <= 17) || (pin >= 29 && pin <= 33) || (pin == 38))
    {
        *pRCC_APB2_ENR  |=  (1<<2);                       // Enable Clock on port A
        pPORT_CRH       =   (uint32_t*)(GPIO_A + 0x04);   // Port B Control Register High (Pin 8 to pin 15)
        pPORT_CRL       =   (uint32_t*)(GPIO_A + 0x00);   // Port B Control Register Low  (Pin 0 to pin 7)
        pODR            =   (uint32_t*)(GPIO_A + 0x0C);   // Port B Output Data Register
        pIDR            =   (uint32_t*)(GPIO_A + 0x08);   // Port B input Data Register        
        if (pin >= 10 && pin <= 17) {pinNum = pin - 10; pPORT_Ctr_Reg = pPORT_CRL;}
        else if (pin >= 29 && pin <= 33) {pinNum = pin - 21; pPORT_Ctr_Reg = pPORT_CRH;}    
        else if (pin == 38) {pinNum = pin - 23; pPORT_Ctr_Reg = pPORT_CRH;}    
        pinBit          =   get_pin_bit(pinNum);
    }
    // Port "B" Initialization
    else if (pin == 19 || (pin >= 39 && pin <= 46) || (pin >= 25 && pin <= 28) || (pin == 21) || (pin == 22))
    {
        *pRCC_APB2_ENR  |=  (1<<3);                       // Enable Clock on port B
        pPORT_CRH       =   (uint32_t*)(GPIO_B + 0x04);   // Port B Control Register High (Pin 8 to pin 15)
        pPORT_CRL       =   (uint32_t*)(GPIO_B + 0x00);   // Port B Control Register Low  (Pin 0 to pin 7)
        pODR            =   (uint32_t*)(GPIO_B + 0x0C);   // Port B Output Data Register
        pIDR            =   (uint32_t*)(GPIO_B + 0x08);   // Port B input Data Register        
        if (pin == 19 || pin == 18) {pinNum = pin - 18; pPORT_Ctr_Reg = pPORT_CRL;}
        else if (pin == 45 || pin == 46) {pinNum = pin - 37; pPORT_Ctr_Reg = pPORT_CRH;}    
        else if (pin >= 39 && pin <= 43) {pinNum = pin - 36; pPORT_Ctr_Reg = pPORT_CRL;}
        else if (pin == 22 || pin == 21) {pinNum = pin - 11; pPORT_Ctr_Reg = pPORT_CRH;}
        else if (pin >= 25 && pin <= 28) {pinNum = pin - 13; pPORT_Ctr_Reg = pPORT_CRH;}
        pinBit          =   get_pin_bit(pinNum);
 
    }
    // Port "C" Initialization
    else if (pin >= 2 && pin <= 4)   // if a pin from port C is selected
    {
        *pRCC_APB2_ENR  |=  (1<<4);                       // Enable Clock on port C
        pPORT_CRH       =   (uint32_t*)(GPIO_C + 0x04);   // Port C Control Register High (Pin 8 to pin 15)
        pPORT_CRL       =   (uint32_t*)(GPIO_C + 0x00);   // Port C Control Register Low  (Pin 0 to pin 7)
        pODR            =   (uint32_t*)(GPIO_C + 0x0C);   // Port C Output Data Register
        pIDR            =   (uint32_t*)(GPIO_C + 0x08);   // Port C input Data Register
        pinNum          =   pin + 11;                     // Example, if pin PC13 is selected, coresponding MCU pin number = 2, therefore 2 + 11 = 13, 13 can be used for pin-bit direct mapping in some registers i.e IDR and ODR
        pPORT_Ctr_Reg   =   pPORT_CRH;                    // Because the usable port C pins are in the CRH range
        pinBit          =   get_pin_bit(pinNum);

    }



    /* Evaluating Pin Modes and Configuring Pins */ 
    switch (mode)
    {

    /* General Purpose Configurations: Push-Pull */
    case 1: // OUTPUT GEN PURP Push-Pull 2 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x2 << pinBit);
        break;
    
    case 2: // OUTPUT GEN PURP Push-Pull 10 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x1 << pinBit);
        break;
    
    case 3: // OUTPUT GEN PURP Push-Pull 50 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |=  (0x3 << pinBit);
        break;

    /* General Purpose Configurations: Open-Drain  */
    case 4: // OUTPUT GEN PURP Open-Drain 2 MHZ (0b0110 = 0x6)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x6 << pinBit);
        break;
    
    case 5: // OUTPUT GEN PURP Open-Drain 10 MHZ (0b0101 = 0x5)
        *pPORT_Ctr_Reg &= ~(0xf <<pinBit);      /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x5 << pinBit);
        break;
    
    case 6: // OUTPUT GEN PURP Open-Drain 50 MHZ (0b0111 = 0x7)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |=  (0x7 << pinBit);
        break;  


    // Alternate Function Configurations: Push-Pull (0b10 = 0x2)
    case 7: // Alt Func Push-Pull 2 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0xa << pinBit);     // 0b1010 = 0xa
        break;
    
    case 8: // Alt Func Push-Pull 10 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x9 << pinBit);     // 0b1001 = 0x9
        break;
    
    case 9: // Alt Func Push-Pull 50 MHZ
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |=  (0xb << pinBit);    // 0b1011 = 0xb
        break;

    /* Alternate Function Configurations: Open-Drain (0b11 = 0x3) */
    case 10: // Alt Func Open-Drain 2 MHZ (0b1110 = 0x6)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0xe << pinBit);     // 0b1110 = 0xe = 14
        break;
    
    case 11: // Alt Func Open-Drain 10 MHZ (0b1101 = 0x5)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x13 << pinBit);     // 0b1101 = 0x13
        break;
    
    case 12: // Alt Func Open-Drain 50 MHZ (0b1111 = 0x7)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |=  (0xf << pinBit);    // 0b1111 = oxf
        break;  

    /* Input Modes Configurations */
    case 13: // Input: Analog Mode
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x0 << pinBit);     // 0b 0000
        break;
    case 14: // Input: Floating Mode (reset state)
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x4 << pinBit);     // 0b0100
        break;
    case 15: // Input: Pull-UP
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x8 << pinBit);      // 0b1000
        *pODR |= (1<<pinNum);                   // ODR BIT = 1
        break;
    case 16: // Input: Pull-Down
        *pPORT_Ctr_Reg &= ~(0xf << pinBit);     /* Zero out all the corresponding pin's MODE and CNF bits */
        *pPORT_Ctr_Reg |= (0x8 << pinBit);      // 0b1000
        *pODR &= ~(1<<pinNum);                  // ODR BIT = 0
        break;

    default:
        /* If the mode selected is not correct then resert the Control Registers to defaults */
        *pPORT_CRH = 0x44444444;
        *pPORT_CRL = 0x44444444;
        break;
    } // End  pin mode Switch
} // End pinModes function

/* This function must be used only when the pin is already set as an input pullup or pulldown and returns 1 for High and 0 for Low */
int digitalRead(int pin)
{

    // Port "A" Initialization
    if ((pin >= 10 && pin <= 17) || (pin >= 29 && pin <= 33) || (pin == 38))
    {
        pIDR    =   (uint32_t*)(GPIO_A + 0x08);   // Port A input Data Register        
        if (pin >= 10 && pin <= 17) {pinNum = pin - 10;}
        else if (pin >= 29 && pin <= 33) {pinNum = pin - 21;}    
        else if (pin == 38) {pinNum = pin - 23;}    
    }
    // Port "B" Initialization
    else if (pin == 19 || (pin >= 39 && pin <= 46) || (pin >= 25 && pin <= 28) || (pin == 21) || (pin == 22))
    {
        pIDR    =   (uint32_t*)(GPIO_B + 0x08);   // Port B input Data Register        
        if (pin == 19 || pin == 18) {pinNum = pin - 18;}
        else if (pin == 45 || pin == 46) {pinNum = pin - 37;}    
        else if (pin >= 39 && pin <= 43) {pinNum = pin - 36;}
        else if (pin == 22 || pin == 21) {pinNum = pin - 11;}
        else if (pin >= 25 && pin <= 28) {pinNum = pin - 13;}
    }    
    // Port "C" Initialization
    else if (pin >= 2 && pin <= 4)   // if a pin from port C is selected
    { 
        pIDR            =   (uint32_t*)(GPIO_C + 0x08);   // Port C input Data Register
        pinNum          =   pin + 11;                     // Example, if pin PC13 is selected, coresponding MCU pin number = 2, therefore 2 + 11 = 13, 13 can be used for pin-bit direct mapping in some registers i.e IDR and ODR
    }

    // Read pin status (High IDR = 1, Low IDR = 0)
    uint16_t input_status = (uint16_t)(*pIDR & (1<<pinNum));
    if (input_status)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}   // End Digital Read Function

/* This function must be used only when the pin is set to Output mode, it outputs digital HIGH and LOW to the pins configured as output, pin e.g PC13, output is either HIGH or LOW*/
void digitalWrite(uint8_t pin, uint8_t output) 
{

    /* For port "A" pins */
    if ((pin >= 10 && pin <= 17) || (pin >= 29 && pin <= 33) || (pin == 38))
    {
        pODR    =   (uint32_t*)(GPIO_A + 0x0C);             // Port A Output Data Register
        if (pin >= 10 && pin <= 17) {pinNum = pin - 10;}
        else if (pin >= 29 && pin <= 33) {pinNum = pin - 21;}    
        else if (pin == 38) {pinNum = pin - 23;}    
    }
    /* For port "B" pins */
    if (pin == 19 || (pin >= 39 && pin <= 46) || (pin >= 25 && pin <= 28) || (pin == 21) || (pin == 22))
    {
        pODR    =   (uint32_t*)(GPIO_B + 0x0C);             // Port B Output Data Register
        if (pin == 19 || pin == 18) {pinNum = pin - 18;}
        else if (pin == 45 || pin == 46) {pinNum = pin - 37;}    
        else if (pin >= 39 && pin <= 43) {pinNum = pin - 36;}
        else if (pin == 22 || pin == 21) {pinNum = pin - 11;}
        else if (pin >= 25 && pin <= 28) {pinNum = pin - 13;} 
    }
    
    /* For port "C" pins */
    else if (pin >= 2 && pin <= 4)   // if a pin from port C is selected
    {
        pODR            =   (uint32_t*)(GPIO_C + 0x0C);     // Port C Output Data Register
        pinNum          =   pin + 11;
    }

    /* Set/Clear pin ODR bits */
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



/* Gets the first bit number which is MODE 0th Bit for each pin in CNF[1:0]-MODE[1:0] or 0b0000 in CRx register (x = high or low) */
uint8_t get_pin_bit(uint8_t pinNum)
{
    // ===================================== Convert into switch statement!
    if(pinNum == 0)  return 0 ;
    else if(pinNum == 1)  return 4 ;
    else if(pinNum == 2)  return 8 ;
    else if(pinNum == 3)  return 12;
    else if(pinNum == 4)  return 16;
    else if(pinNum == 5)  return 20;
    else if(pinNum == 6)  return 24;
    else if(pinNum == 7)  return 28;
    else if(pinNum == 8)  return 0;
    else if(pinNum == 9)  return 4;
    else if(pinNum == 10) return 8;
    else if(pinNum == 11) return 12;
    else if(pinNum == 12) return 16;
    else if(pinNum == 13) return 20;
    else if(pinNum == 14) return 24;
    else if(pinNum == 15) return 28;
    else return 0;
}


#endif // Header Guarding End