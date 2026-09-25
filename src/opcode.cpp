#include "../include/opcode.h"
#include "../include/cpu.h"

#define INSTRUCTION(name) void name(CPU* cpu, uint8_t opcode)
#define INSTR_SINGLE 1
#define INSTR_DOUBLE 2
#define INSTR_TRIPLE 3

Instruction optable_main[N_INSTRS];
Instruction optable_extended[N_INSTRS];

INSTRUCTION(no_op) {
    advance_pc(cpu, INSTR_SINGLE);
}

INSTRUCTION(stop) {
    fetch_8(cpu);
    cpu_stop(cpu);
}

static void mv_16_imm(uint8_t* reg1, uint8_t* reg2, uint16_t imm) {
    *reg1 = imm >> 8;
    *reg2 = imm & 0xFF;
}

static void add_8(CPU* cpu, )

INSTRUCTION(ld_16_imm) {
    uint8_t reg = opcode >> 4;
    uint16_t imm = fetch_16(cpu);
    switch (reg) {
    case 0x0:
        mv_16_imm(&cpu->B, &cpu->C, imm);
        break;
    case 0x1:
        mv_16_imm(&cpu->D, &cpu->E, imm);
        break;
    case 0x2:
        mv_16_imm(&cpu->H, &cpu->L, imm);
        break;
    case 0x3:
        cpu->SP = imm;
        break;
    default:
        break;
    }
}

INSTRUCTION(st_8_a) {
    uint8_t sel = opcode >> 4;
    
}

INSTRUCTION(jr) {
    uint8_t offset = fetch_8(cpu);
    uint8_t flag = opcode >> 4;
    bool invert = (opcode & 0xF) == 0x8;
    bool jump = false;
    if (flag == 0x1) {
        jump = true;
    } else {
        uint8_t flag_mask = flag == 0x2 ? FLAG_ZERO : FLAG_FCAR;
        bool flag_set = cpu_get_flag(cpu, flag_mask);
        jump = (flag_set && invert) || (!flag_set && !invert);
    }
    if (jump) {
        advance_pc(cpu, offset);
    }
}

INSTRUCTION(inc_8) {
    uint8_t reg = opcode >> 3;

}

static void init_main() {
    optable_main[0x00] = no_op;

}

static void init() {

}

void gen_optables() {
    static bool initialized = false;
    if (!initialized) {
        init();
        initialized = true;
    }
}