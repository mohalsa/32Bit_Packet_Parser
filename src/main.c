/*
    This is a packet field extraction programme.
    A packet example is in the packets header file, change accordingly
    To debug this project:
    1- Run the "Allow debuggind for any STM32 ..etc.. " task
    2- Add some break points (5 Max) and Run the debugger "PIO Debug"

    To allow uploading a new code to the MCU you must terminate the "Allow debuggin for any STM32 ... " task first!
    if still not uploading, terminate the "OpenOCD" task on the Activity monitor(MAC) or Task Manager(Windows)
    because this is a known issue!

    By Mohammed Alsada
    Github: https://github.com/mohalsa
*/
#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "FRAMEWORK.h"
#include "packets.h"
#include <inttypes.h>   // Used for the scansets and printsets i.e SCNx32

void clearBuffer(void);


uint32_t packet_32bit = 0;

int main(void)
{
    while(1)
    {
        clearBuffer();
        printf("Enter the recieved 32Bits packet value:\n");
        scanf("%lx", &packet_32bit);
        printf("Your packet value is: %lX\n", packet_32bit);
        fflush(stdout);
    }
}

void clearBuffer(void)
{
    uint8_t c;
    while ( (c = getchar()) != '\n' && c != EOF)
    {
        // Keep looping and parsing getchar into variable c untill nothing is left in the buffer
        // until the enter is pressed and it has to be the last thing entered or end of file!
    }
}
