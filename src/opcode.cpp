#include "../include/opcode.h"
#include "../include/cpu.h"

#define INSTRUCTION(name) void name(CPU* cpu, uint8_t opcode)
#define INSTR_SINGLE 1
#define INSTR_DOUBLE 2
#define INSTR_TRIPLE 3

Instruction optable_main[N_INSTRS];
Instruction optable_extended[N_INSTRS];

INSTRUCTION(no_op) { cpu_advance_pc(cpu, INSTR_SINGLE); }

INSTRUCTION(stop) {
    cpu_fetch_8(cpu);
    cpu_stop(cpu);
}

INSTRUCTION(ld_8_imm) {
    Reg8 reg = Reg8((opcode >> 3) & 0b111);
    uint8_t imm = cpu_fetch_8(cpu);
    cpu_mv_8_imm(cpu, reg, imm);
}

INSTRUCTION(ld_16_imm) {
    Reg16 reg = Reg16(opcode >> 4);
    uint16_t imm = cpu_fetch_16(cpu);
    cpu_mv_16_imm(cpu, reg, imm);
}

INSTRUCTION(ld_8) {
    Reg8 reg_dest = Reg8((opcode >> 3) & 0b111);
    Reg8 reg_src = Reg8(opcode & 0b111);
    cpu_mv_8(cpu, reg_dest, reg_src);
}

INSTRUCTION(st_8_mem) {
    uint8_t sel = opcode >> 4;
    
}

INSTRUCTION(jr) {
    uint8_t offset = cpu_fetch_8(cpu);
    uint8_t modifier = opcode >> 4;
    bool invert = (opcode & 0xF) == 0x8;
    bool jump = false;
    if (modifier == 0x1) {
        jump = true;
    } else {
        uint8_t flag = modifier == 0x2 ? Flag::Zero : Flag::FullCarry;
        bool flag_set = cpu_get_flag(cpu, flag);
        jump = flag_set == invert;
    }
    if (jump) {
        cpu_advance_pc(cpu, offset);
    }
}

INSTRUCTION(inc_8) {
    Reg8 reg = Reg8((opcode >> 3) & 0b111);
    cpu_inc_8(cpu, reg);
}

INSTRUCTION(dec_8) {
    Reg8 reg = Reg8((opcode >> 3) & 0b111);
    cpu_dec_8(cpu, reg);
}

INSTRUCTION(inc_16) {
    Reg16 reg = Reg16(opcode >> 4);
    cpu_inc_16(cpu, reg);
}

INSTRUCTION(dec_16) {
    Reg16 reg = Reg16(opcode >> 4);
    cpu_dec_16(cpu, reg);
}

static void init_main() { optable_main[0x00] = no_op; }

static void init() {}

void gen_optables() {
    static bool initialized = false;
    if (!initialized) {
        init();
        initialized = true;
    }
}
