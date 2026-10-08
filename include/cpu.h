#ifndef CPU_H
#define CPU_H

#include <cstdint>

struct Memory;

enum Flag : uint8_t {
    FullCarry = 4,
    HalfCarry = 5,
    Subtract = 6,
    Zero = 7,
};

typedef struct CPU {
    union {
        uint16_t BC;
        struct {
            uint8_t C, B;
        };
    };
    union {
        uint16_t DE;
        struct {
            uint8_t E, D;
        };
    };
    union {
        uint16_t HL;
        struct {
            uint8_t L, H;
        };
    };
    union {
        uint16_t AF;
        struct {
            uint8_t F, A;
        };
    };
    uint16_t SP, PC;
    bool stopped;
} CPU;

enum Reg8 : uint8_t {
    B = 0x0,
    C = 0x1,
    D = 0x2,
    E = 0x3,
    H = 0x4,
    L = 0x5,
    _HL = 0x6,
    A = 0x7,
    F = 0x8,
};

enum Reg16 : uint8_t {
    BC = 0,
    DE,
    HL,
    SP,
    AF,
    PC,
};

void cpu_advance_pc(CPU*, uint16_t);
uint8_t cpu_fetch_8(CPU*);
uint16_t cpu_fetch_16(CPU*);
void cpu_stop(CPU*);
bool cpu_get_flag(CPU*, uint8_t);

void cpu_mv_8(CPU*, Reg8, Reg8);
void cpu_mv_16(CPU*, Reg16, Reg16);
void cpu_mv_8_imm(CPU*, Reg8, uint8_t);
void cpu_mv_16_imm(CPU*, Reg16, uint16_t);

void cpu_add_8(CPU*, Reg8, Reg8);
void cpu_adc_8(CPU*, Reg8, Reg8);
void cpu_add_16(CPU*, Reg16, Reg16);

#endif
