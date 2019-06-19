#pragma once
#include <map>
#include "PPURegisters.h"

namespace mem {
	// The memory is actually divided into 3 parts but they're so tightly coupled
	// in the hardware that it is much easier to just group them all together

	class Memory {
	public:
		void WriteByte(uint16_t address, uint8_t value);
		void WriteWord(uint16_t address, uint16_t value);

		uint8_t ReadByte(uint16_t address);
		uint16_t ReadWord(uint16_t address);

		uint8_t ReadPPUReg(uint16_t address);

	private:
		uint16_t GetAbsoluteAddress(uint16_t address);
		void IncrementAddressLatch();
		void OAMDump(uint8_t value);

		uint8_t vramBuffer;

		using MemComponent = std::map<uint16_t, uint8_t>;
		MemComponent memory;
		MemComponent VRAM;
		MemComponent attributeMemory;
		MemComponent cartridgeMemory;
	};
}