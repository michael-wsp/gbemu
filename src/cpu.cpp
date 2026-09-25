#include "../include/cpu.h"
#include "../include/memory.h"

bool cpu_get_flag(CPU* cpu, uint8_t flag_mask) {
    return (cpu->F & flag_mask) == flag_mask;
}

void cpu_stop(CPU* cpu) {
    cpu->stopped = true;
}

void advance_pc(CPU* cpu, uint16_t steps) {
    cpu->PC += steps;
}

uint8_t fetch_8(CPU* cpu) {
    uint8_t val = mem_load_8(cpu->PC);
    advance_pc(cpu, 1);
    return val;
}

uint16_t fetch_16(CPU* cpu) {
    uint16_t val = mem_load_16(cpu->PC);
    advance_pc(cpu, 2);
    return val;
}