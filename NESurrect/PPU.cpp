#include "PPU.h"

namespace ppu {
	PPU::PPU(mem::Memory *mem, wrapper::Wrapper *wrapper) {
		this->mem_ = mem;
		this->wrapper_ = wrapper;
		cycleNum_ = 0;
		scanlineNum_ = 0;
		state = State::PRERENDER;
	}

	void PPU::runCycle() {
		updateState();

		switch (state) {
		case State::LOADING:
			break;

		case State::PRERENDER:
			break;

		case State::RENDER:
			generateBGPixel();
			break;

		case State::POSTRENDER:
			wrapper_->RenderPixels(pixels_.data());
			pixels_.clear();
			vramAddress_ = 0;
			break;

		case State::VBLANK_START:
			startVBlank();
			break;

		case State::VBLANK:
			break;

		case State::VBLANK_END:
			endVBlank();
		}
	}

	void PPU::updateState() {
		cycleNum_++;
		if (cycleNum_ > 340) {
			cycleNum_ = 0;
			scanlineNum_++;
		}

		if (cycleNum_ >= 256) {
			state = State::LOADING;
			return;
		}

		if (scanlineNum_ == -1) {
			state = State::PRERENDER;
		} else if (scanlineNum_ < 240) {
			state = State::RENDER;
		} else if (scanlineNum_ == 240) {
			state = State::POSTRENDER;
		} else if (scanlineNum_ == 241) {
			state = State::VBLANK_START;
		} else if (scanlineNum_ < 260) {
			state = State::VBLANK;
		} else if (scanlineNum_ == 260) {
			state = State::VBLANK_END;
		} else {
			scanlineNum_ = 0;
		}
	}

	void PPU::startVBlank() {
		if (scanlineNum_ == 241 && cycleNum_ == 1) {
			mem_->writeByte(REG_STATUS, mem_->peek(REG_STATUS) | MASK_NMI_ENABLE);
		}
	}

	void PPU::endVBlank() {
		if (cycleNum_ == 1) {
			mem_->readByte(REG_STATUS);
		}
	}

	void PPU::generateBGPixel() {
		uint8_t x, y;
		x = cycleNum_ / 8;
		y = scanlineNum_ / 8;

		// Load a new tile
		if (scanlineNum_ % 8 == 0 && cycleNum_ % 8 == 0)
		{
			uint16_t VRAMOffset = NAMETABLE_START + ((mem_->peekVram(REG_CTRL) & MASK_BASE_NAMETABLE) * NAMETABLE_LENGTH);
			uint16_t nametableIndex = mem_->peekVram(VRAMOffset + (x + (y * 32)));
			uint16_t attributeData =  mem_->peekVram(VRAMOffset + (x + (y * 32)) + 0x03C0);
			nametable_[x][y] = nametableIndex;
			attributetable_[x][y] = attributeData;
		}

		if (cycleNum_ % 8 == 0)
		{
			// Determine whether to use the left or right background table by reading PPUCtrl
			uint16_t nametableOffset = NAMETABLE_INDEX_OFFSET * ((mem_->peekVram(REG_CTRL) & MASK_BG_TABLE) > 0);
			nametableOffset = 0x1000;

			// Each tile in the pattern table is size 0x10, and the second half is 0x08 after the first.
			bitmapRegister_[0] = mem_->peekVram(nametableOffset + (nametable_[x][y] * PATTERN_SPRITE_SIZE) + (scanlineNum_ % 8));
			bitmapRegister_[1] = mem_->peekVram(nametableOffset + (nametable_[x][y] * PATTERN_SPRITE_SIZE) + (scanlineNum_ % 8) + PATTERN_SPRITE_HALF_OFFSET);
			//bitmapRegister_[0] = mem_->peekVram(0x1000 + ((x + (y * 24)) * PATTERN_SPRITE_SIZE) + (scanlineNum_ % 8));
			//bitmapRegister_[1] = mem_->peekVram(0x1000 + ((x + (y * 24)) * PATTERN_SPRITE_SIZE) + (scanlineNum_ % 8) + PATTERN_SPRITE_HALF_OFFSET);
		}


		uint8_t	px = (bitmapRegister_[0] >> (7 - (cycleNum_ % 8)) & 0x01);
		px += (bitmapRegister_[1] >> (7 - (cycleNum_ % 8)) & 0x01) << 1;
		px *= 84;

		pixels_.push_back(px);
		pixels_.push_back(px);
		pixels_.push_back(px);
		pixels_.push_back(px);
	}
}