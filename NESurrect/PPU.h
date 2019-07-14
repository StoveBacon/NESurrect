#pragma once
#include <cstdint>
#include <vector>
#include "Memory.h"
#include "WrapperTypes.h"

namespace ppu {

	class PPU {
	public:
		PPU(mem::Memory *mem, wrapper::Wrapper *wrapper);
		void runCycle();

	private:
		uint16_t generateBGPixel();

		std::vector<uint8_t> pixels_;
		int cycleNum_;

		// Background rendering
		uint8_t vramAddress_;
		uint8_t fineXScroll_;
		uint16_t bitmapRegister_[2];
		uint8_t paletteRegister_[2];

		// Sprite rendering


		mem::Memory *mem_;
		wrapper::Wrapper *wrapper_;
	};
}