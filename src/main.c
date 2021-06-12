/*
    This is a packet field extraction programme.
    A packet example is in the packets header file, change accordingly
    To debug this project:
    1- Run the "Allow debuggin for any STM32 ..etc.. " task
    2- In the debugger, select the printf & scanf enabled - PIO build and debug active file option
    3- An external consol will open, this is where you are going to interact with the program

    To allow uploading a new code to the MCU you must terminate the "Allow debuggin for any STM32 ... " task first!

    By Mohammed Alsada
    Github: https://github.com/mohalsa
*/
#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "FRAMEWORK.h"
#include "packets.h"
#include <inttypes.h>   // Used for the scansets and printsets i.e SCNx32


uint32_t packet_32bit = 0;

int main(void)
{
    while(1)
    {
        printf("\nEnter the recieved 32Bits packet value: ");
        scanf("%ld", &packet_32bit);
        printf("\nYour packet value is: %lX, Press any key to exit", packet_32bit);
        getchar();
    }
}
