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
		void generateBGPixel();

		std::vector<uint8_t> pixels_;
		int cycleNum_;
		int scanlineNum_;

		enum class State { LOADING, PRERENDER, RENDER, POSTRENDER, VBLANK_START, VBLANK, VBLANK_END };
		State state;
		void updateState();

		void startVBlank();
		void endVBlank();

		// Background rendering
		uint16_t vramAddress_;
		uint8_t fineXScroll_;
		uint16_t bitmapRegister_[2];
		uint8_t paletteRegister_[2];
		uint8_t nametable_[32][30];
		uint8_t attributetable_[32][30];

		// Sprite rendering


		mem::Memory *mem_;
		wrapper::Wrapper *wrapper_;
	};
}