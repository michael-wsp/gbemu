#ifndef OPCODE_H
#define OPCODE_H

#include <cstdint>

#define N_INSTRS 256

typedef struct CPU CPU;

using Instruction = void (*)(CPU*, uint8_t);

void execute_instr(CPU* cpu);

void gen_optables();

#endif