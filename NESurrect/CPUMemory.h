#pragma once
#include "Memory.h"

namespace memory {
	constexpr int MemSize = 0x10000U;
	constexpr uint16_t RAMMirrorLow = 0x0000U;
	constexpr uint16_t RAMMirrorHigh = 0x2000U;
	constexpr uint16_t RAMMirrorSize = 0x0800U;
	constexpr uint16_t PPUMirrorLow = 0x2000U;
	constexpr uint16_t PPUMirrorHigh = 0x4000U;
	constexpr uint16_t PPUMirrorSize = 0x08U;

	class CPUMemory : public Memory<MemSize, RAMMirrorLow, RAMMirrorHigh, RAMMirrorSize, PPUMirrorLow, PPUMirrorHigh, PPUMirrorSize> {
	public:
		void Write(const uint16_t address, const uint8_t data) {
			cycles++;
			Memory::Write(address, data);
		}
		uint8_t Read(const uint16_t address) {
			cycles++;
			return Memory::Read(address);
		}

		// Cycles are tracked in order to catch up the other components of the system while maintaining accuracy
		// They will be reset every time an instruction is completed
		int cycles = 0;
	};
}
