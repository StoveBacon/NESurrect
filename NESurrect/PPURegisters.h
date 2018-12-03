#pragma once
#include <cstdint>


namespace PPU {
	// For information on what each of these is, visit:
	// http://wiki.nesdev.com/w/index.php/PPU_registers
	// Define each register and each offset into it
	constexpr uint16_t PPUCtrl = 0x2000;
	constexpr uint8_t NMIEnable = 0x80;
	constexpr uint8_t PPUMaster = 0x40;
	constexpr uint8_t SpriteHeight = 0x20;
	constexpr uint8_t BGTile = 0x10;
	constexpr uint8_t SpriteTile = 0x08;
	constexpr uint8_t IncMode = 0x40;
	constexpr uint8_t Nametable = 0x03;

	constexpr uint16_t PPUMask = 0x2001;
	constexpr uint8_t ColorEmphasis = 0xE0;
	constexpr uint8_t SpriteEnable = 0x10;
	constexpr uint8_t BGEnable = 0x08;
	constexpr uint8_t SpriteLC = 0x04;
	constexpr uint8_t SpriteRC = 0x02;
	constexpr uint8_t Grayscale = 0x01;

	constexpr uint16_t PPUStatus = 0x2002;
	constexpr uint8_t VBlank = 0x80;
	constexpr uint8_t SpriteZero = 0x40;
	constexpr uint8_t SpriteOverflow = 0x20;
	
	// The rest of the registers are for transfering data, they don't need any masks
	constexpr uint16_t OAMAddress = 0x2003;
	constexpr uint16_t OAMData = 0x2004;
	constexpr uint16_t PPUScroll = 0x2005;
	constexpr uint16_t PPUAddress = 0x2006;
	constexpr uint16_t PPUData = 0x2007;
	constexpr uint16_t OAMDATA = 0x4014;


	class PPURegisters {
	public:

	private:
	
	};
}