#include "PPU.h"

namespace ppu {
	PPU::PPU(mem::Memory *mem, wrapper::Wrapper *wrapper) {
		this->mem_ = mem;
		this->wrapper_ = wrapper;
		cycleNum_ = 0;
	}

	void PPU::runCycle() {

	}

	uint16_t PPU::generateBGPixel() {
		// New data is needed every 8th cycle only
		if (cycleNum_ % 8 == 0) {

			// -- Load background shift registers --

			// Determine which name table to read from. Values 0-3 select the name table offset, which increments by the table length
			uint16_t VRAMOffset = NAMETABLE_START + ((mem_->peekVram(REG_CTRL) & MASK_BASE_NAMETABLE) * NAMETABLE_LENGTH);
			uint16_t nametableIndex = mem_->peekVram(vramAddress_ + VRAMOffset);
			uint16_t attributeData = mem_->peekVram(vramAddress_ + VRAMOffset + 0x03C0);
			vramAddress_ += NAMETABLE_ENTRY_SIZE;

			// Determine whether to use the left or right background table by reading PPUCtrl
			uint16_t nametableOffset = NAMETABLE_INDEX_OFFSET * ((mem_->peekVram(REG_CTRL) & MASK_BG_TABLE) > 0);

			// Each tile in the pattern table is size 0x10, and the second half is 0x08 after the first.
			bitmapRegister_[0] = mem_->peekVram(nametableOffset + (nametableIndex * PATTERN_SPRITE_SIZE));
			bitmapRegister_[1] = mem_->peekVram(nametableOffset + (nametableIndex * PATTERN_SPRITE_SIZE) + PATTERN_SPRITE_HALF_OFFSET);
		}
		

		return 0;
	}
}