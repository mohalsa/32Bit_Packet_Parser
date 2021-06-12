#ifndef PACKETS_H_
#define PACKETS_H_
#include <stdint.h>

typedef struct
{
    uint8_t crc;
    uint8_t status;
    uint16_t payload;
    uint8_t battery;
    uint8_t sensor;
    uint8_t longAddr;
    uint8_t shortAddr;
    uint8_t addrMode;
}packet;





#endif