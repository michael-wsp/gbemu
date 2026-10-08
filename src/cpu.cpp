#include "../include/cpu.h"
#include "../include/memory.h"

uint8_t* reg8_ptr(CPU* cpu, Reg8 reg) {
    static constexpr uint8_t CPU::* regs_8[] = {&CPU::B, &CPU::C, &CPU::D,
                                                &CPU::E, &CPU::H, &CPU::L,
                                                nullptr, // [HL]
                                                &CPU::A, &CPU::F};

    if (reg == Reg8::_HL) {
        return nullptr;
    }

    return &(cpu->*regs_8[reg]);
}

uint16_t* reg16_ptr(CPU* cpu, Reg16 reg) {
    static constexpr uint16_t CPU::* regs_16[] = {&CPU::BC, &CPU::DE, &CPU::HL,
                                                  &CPU::SP, &CPU::AF, &CPU::PC};

    return &(cpu->*regs_16[reg]);
}

uint8_t reg8_get(CPU* cpu, Reg8 reg) {
    return *reg8_ptr(cpu, reg);
}

uint16_t reg16_get(CPU* cpu, Reg16 reg) {
    return *reg16_ptr(cpu, reg);
}

bool cpu_get_flag(CPU* cpu, Flag flag) {
    uint8_t flag_mask = 0x01 << flag;
    return (cpu->F & flag_mask) == flag_mask;
}

void cpu_set_flag(CPU* cpu, Flag flag, bool value) {
    uint8_t flag_set = uint8_t(value) << flag;
    uint8_t flag_unset = ~(0x01 << flag);
    cpu->F = (cpu->F & flag_unset) | flag_set;
}

void add_8(CPU* cpu, uint8_t* dest, uint8_t* src, bool carry) {
    uint8_t a = *dest;
    uint8_t b = *src;
    bool carry_in = carry && cpu_get_flag(cpu, Flag::FullCarry);
    uint16_t sum = uint16_t(a) + uint16_t(b) + uint16_t(carry_in);
    bool full = sum > 0xFF;
    bool half = ((a & 0x0F) + (b & 0x0F) + carry_in) > 0x0F;
    cpu_set_flag(cpu, Flag::FullCarry, full);
    cpu_set_flag(cpu, Flag::HalfCarry, half);
    *dest = sum & 0xFF;
}

void add_16(CPU* cpu, uint16_t* dest, uint16_t* src, bool carry) {
    uint16_t a = *dest;
    uint16_t b = *dest;
    bool carry_in = carry & cpu_get_flag(cpu, Flag::FullCarry);
    uint32_t sum = uint32_t(a) + uint32_t(b) + uint32_t(carry_in);
    bool full = sum > 0xFFFF;
    bool half = ((a & 0x0FFF) + (b & 0x0FFF)) > 0x0FFF;
    cpu_set_flag(cpu, Flag::FullCarry, full);
    cpu_set_flag(cpu, Flag::HalfCarry, half);
    *dest = sum & 0xFFFF;
}

void cpu_stop(CPU* cpu) { cpu->stopped = true; }

void advance_pc(CPU* cpu, uint16_t steps) { cpu->PC += steps; }

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

void cpu_mv_8(CPU* cpu, Reg8 dest, Reg8 src) {
    uint8_t* dest_ptr = reg8_ptr(cpu, dest);
    uint8_t* src_ptr = reg8_ptr(cpu, src);
    *dest_ptr = *src_ptr;
}

void cpu_mv_16(CPU* cpu, Reg16 dest, Reg16 src) {
    uint16_t* dest_ptr = reg16_ptr(cpu, dest);
    uint16_t* src_ptr = reg16_ptr(cpu, src);
    *dest_ptr = *src_ptr;
}

void cpu_mv_8_imm(CPU* cpu, Reg8 dest, uint8_t imm) {
    uint8_t* dest_ptr = reg8_ptr(cpu, dest);
    *dest_ptr = imm;
}
void cpu_mv_16_imm(CPU* cpu, Reg16 dest, uint16_t imm) {
    uint16_t* dest_ptr = reg16_ptr(cpu, dest);
    *dest_ptr = imm;
}

void cpu_add_8(CPU* cpu, Reg8 dest, Reg8 src, bool carry) {
    uint8_t* dest_ptr = reg8_ptr(cpu, dest);
    uint8_t* src_ptr = reg8_ptr(cpu, src);
    add_8(cpu, dest_ptr, src_ptr, carry);
}

void cpu_add_16(CPU* cpu, Reg16 dest, Reg16 src, bool carry) {
    uint16_t* dest_ptr = reg16_ptr(cpu, dest);
    uint16_t* src_ptr = reg16_ptr(cpu, src);
    add_16(cpu, dest_ptr, src_ptr, carry);
}

void cpu_inc_8(CPU* cpu, Reg8 reg) {
    uint8_t inc = 1;
    uint8_t* reg_ptr = reg8_ptr(cpu, reg);
    add_8(cpu, reg_ptr, &inc, false);
}

void cpu_dec_8(CPU* cpu, Reg8 reg) {
    uint8_t dec = static_cast<uint8_t>(-1);
    uint8_t* reg_ptr = reg8_ptr(cpu, reg);
    add_8(cpu, reg_ptr, &dec, false);
}

void cpu_inc_16(CPU* cpu, Reg16 reg) {
    uint16_t inc = 1;
    uint16_t* reg_ptr = reg16_ptr(cpu, reg);
    add_16(cpu, reg_ptr, &inc, false);
}

void cpu_dec_16(CPU* cpu, Reg16 reg) {
    uint16_t dec = static_cast<uint16_t>(-1);
    uint16_t* reg_ptr = reg16_ptr(cpu, reg);
    add_16(cpu, reg_ptr, &dec, false);
}

void cpu_store_8(CPU* cpu, Reg16 addr_reg, Reg8 src) {
    uint16_t addr = reg16_get(cpu, addr_reg);
    uint8_t value = reg8_get(cpu, src);
    mem_store_8(addr, value);
}

void cpu_load_8(CPU* cpu, Reg8 dest, Reg16 addr_reg) {
    uint16_t addr = reg16_get(cpu, addr_reg);
    uint8_t* dest_addr = reg8_ptr(cpu, dest);
    *dest_addr = mem_load_8(addr);
}