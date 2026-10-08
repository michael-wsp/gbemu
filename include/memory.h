#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

uint8_t mem_load_8(uint16_t);
uint16_t mem_load_16(uint16_t);

uint8_t mem_store_8(uint16_t, uint8_t);
uint16_t mem_store_16(uint16_t, uint16_t);

#endif