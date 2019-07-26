#pragma once
#include <cstdint>

// CPU memory
constexpr uint32_t MEM_TOTAL_SIZE = 0x10000;
constexpr uint16_t INTERNAL_RAM_SIZE = 0x800;
constexpr uint16_t REG_PPU_START = 0x2000;
constexpr uint16_t REG_PPU_SIZE = 0x08;
constexpr uint16_t REG_APU_IO_START = 0x4000;
constexpr uint16_t CARTRIDGE_MEM_START = 0x4020;

// PPU memory

// Registers and their masks
constexpr uint16_t REG_CTRL = 0x2000;
constexpr uint8_t MASK_NMI_ENABLE = 0x80;
constexpr uint8_t MASK_PPU_MASTER = 0x40;
constexpr uint8_t MASK_SPRITE_HEIGHT = 0x20;
constexpr uint8_t MASK_BG_TABLE = 0x10;
constexpr uint8_t MASK_SPRITE_TILE = 0x08;
constexpr uint8_t MASK_INC_MODE = 0x40;
constexpr uint8_t MASK_BASE_NAMETABLE = 0x03;

constexpr uint16_t REG_MASK = 0x2001;
constexpr uint8_t MASK_COLOR_EMPH = 0xE0;
constexpr uint8_t MASK_SPRITE_ENABLE = 0x10;
constexpr uint8_t MASK_BG_ENABLE = 0x08;
constexpr uint8_t MASK_SPRITE_LEFT = 0x04;
constexpr uint8_t MASK_SPRITE_RIGHT = 0x02;
constexpr uint8_t MASK_GRAYSCALE = 0x01;

constexpr uint16_t REG_STATUS = 0x2002;
constexpr uint8_t MASK_VBLANK = 0x80;
constexpr uint8_t MASK_SPRITE_ZERO = 0x40;
constexpr uint8_t MASK_SPRITE_OVERFLOW = 0x20;
	
// Unmasked registers
constexpr uint16_t REG_OAM_ADDRESS = 0x2003;
constexpr uint16_t REG_OAM_DATA = 0x2004;
constexpr uint16_t REG_SCROLL = 0x2005;
constexpr uint16_t REG_ADDRESS = 0x2006;
constexpr uint16_t REG_DATA = 0x2007;
constexpr uint16_t REG_OAM_DUMP = 0x4014;

// Memory sizes, table sizes, so on
constexpr uint16_t VRAM_SIZE = 0x4000;
constexpr uint16_t OAM_SIZE = 0x100;
constexpr uint16_t NAMETABLE_START = 0x2000;
constexpr uint16_t NAMETABLE_ENTRY_SIZE = 0x10;
constexpr uint16_t NAMETABLE_LENGTH = 0x400;
constexpr uint16_t NAMETABLE_INDEX_OFFSET = 0x1000;
constexpr uint16_t PATTERN_SPRITE_SIZE = 0x10;
constexpr uint16_t PATTERN_SPRITE_HALF_OFFSET = 0x08;