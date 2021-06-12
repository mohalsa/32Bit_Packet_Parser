/*
    This is a packet field extraction program. Using bitfields structure inside a union which has a variable
    of the same size of the packet intended to be sent or decoded.

    A packet sturcture example is in the packets header file, change accordingly
    To debug this project:
    1- Run the "Allow debuggind for any STM32 ..etc.. " task
    2- Add some break points (5 Max) and,
    3- Run the debugger "PIO Debug"

    To allow uploading a new code to the MCU you must terminate the "Allow debuggin for any STM32 ... " task first!
    if still not uploading, terminate the "OpenOCD" task on the Activity monitor(MAC) or Task Manager(Windows)
    because this is a known issue!

    By Mohammed Alsada
    Github: https://github.com/mohalsa
*/
#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "FRAMEWORK.h"  // Allows Abstraction for pinMode, digitalRead, digitalWrite etc..
#include "packets.h"    // Packet Structure implemetation


// Create a Packet_t unon datatype variable.
Packet_t packet32;

int main(void)
{
    while(1)
    {
        printf("Enter the recieved 32Bits packet value (in HEX format):\n");
        // Read the user entered packet value into the packet_value variable
        scanf("%lx", &packet32.packet_value);
        printf("Your packet value is: %#lX\n\n", packet32.packet_value);
        

        printf("CRC                     : %#X\n", packet32.packetFields_t.crc);
        printf("STATUS                  : %#X\n", packet32.packetFields_t.status);
        printf("PAYLOAD                 : %#X\n", packet32.packetFields_t.payload);
        printf("BATTERY                 : %#X\n", packet32.packetFields_t.battery);
        printf("SENSOR                  : %#X\n", packet32.packetFields_t.sensor);
        printf("LONG_ADDRESS            : %#X\n", packet32.packetFields_t.longAddr);
        printf("SHORT_ADDRESS           : %#X\n", packet32.packetFields_t.shortAddr);
        printf("ADDRESS_MODE            : %#X\n\n", packet32.packetFields_t.addrMode);
        while (getchar() != '\n');
        getchar();
    }
}

