#ifndef PACKETS_H_
#define PACKETS_H_
#include <stdint.h>

/* Using the bitfields (crc:2) = store 2 bits for the variable crc out of the 32bits given */
typedef union
{
    uint32_t packet_value;
    struct
    {
        uint32_t crc        : 2;
        uint32_t status     : 1;
        uint32_t payload    : 12;
        uint32_t battery    : 3;
        uint32_t sensor     : 3;
        uint32_t longAddr   : 8;
        uint32_t shortAddr  : 2;
        uint32_t addrMode   : 1;        
    }packetFields_t;

}Packet_t;





#endif