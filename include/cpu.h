#ifndef CPU_H
#define CPU_H

#include <cstdint>

const uint8_t FLAG_ZERO = 0b10000000;
const uint8_t FLAG_SUB  = 0b01000000;
const uint8_t FLAG_HCAR = 0b00100000;
const uint8_t FLAG_FCAR = 0b00010000;

struct Memory;

typedef struct CPU {
    uint8_t A, B, C, D, E, H, L;
    uint8_t F;
    uint16_t SP, PC;
    bool stopped;
} CPU;

void advance_pc(CPU*, uint16_t);
uint8_t fetch_8(CPU*);
uint16_t fetch_16(CPU*);
void cpu_stop(CPU*);
bool cpu_get_flag(CPU*, uint8_t);

#endif