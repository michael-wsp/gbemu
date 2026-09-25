#include "../include/memory.h"

const uint16_t WRAM_BYTES = 0x2000;
const uint16_t HRAM_BYTES = 0x7F;

const uint16_t ROM0_BASE =      0x0000;
const uint16_t ROMX_BASE =      0x4000;
const uint16_t VRAM_BASE =      0x8000;
const uint16_t CART_RAM_BASE =  0xA000;
const uint16_t WRAM_BASE =      0xC000;
const uint16_t ERAM_BASE =      0xE000;
const uint16_t OAM_BASE =       0xFE00;
const uint16_t NULL_BASE =      0xFE9F;
const uint16_t IO_BASE =        0xFEFF;
const uint16_t HRAM_BASE =      0xFF7F;
const uint16_t INT_BASE =       0xFFFE;

typedef struct Memory {
    uint8_t* rom0;
    uint8_t* romx;
    uint8_t* vram;
    uint8_t* cart_ram;
    uint8_t  wram[WRAM_BYTES];
    uint8_t* oam;
    uint8_t  hram[HRAM_BYTES];
} Memory;


Memory mem;

static uint8_t read_byte(uint16_t addr) {
    if (addr < ROMX_BASE) {
        // cart 1 rom
        return mem.rom0[addr];
    } else if (addr < VRAM_BASE) {
        // cart 2 rom
        return mem.romx[addr - ROMX_BASE];
    } else if (addr < CART_RAM_BASE) {
        // vram
        return mem.vram[addr - VRAM_BASE ];
    } else if (addr < WRAM_BASE) {
        // cart ram
        return mem.cart_ram[addr - CART_RAM_BASE];
    } else if (addr < ERAM_BASE) {
        return mem.wram[addr - WRAM_BASE];
    } else if (addr < OAM_BASE) {
        return mem.wram[addr - ERAM_BASE];
    } else if (addr < NULL_BASE) {
        // sprite
        return mem.oam[addr - OAM_BASE];
    } else if (addr < IO_BASE) {
        // unusable
        return 0;
    } else if (addr < HRAM_BASE) {
        // io
        return 0;
    } else if (addr < INT_BASE) {
        return mem.hram[addr - HRAM_BASE];
    } else {
        // interrupt
        return 0;
    }
}

uint8_t mem_load_8(uint16_t addr) {
    return read_byte(addr);
}

uint16_t mem_load_16(uint16_t addr) {
    uint8_t lo = read_byte(addr);
    uint8_t hi = read_byte(addr + 1);
    return (static_cast<uint16_t>(hi) << 8) | lo;
}