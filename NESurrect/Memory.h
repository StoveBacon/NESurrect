#pragma once
#include <map>
#include "PPURegisters.h"

namespace mem {
	/* The memory is actually divided into 3 parts but they're so tightly coupled
	 * in the hardware that it is much easier to just group them all together
	 */
	class Memory {
	public:
		void WriteByteCPU(uint16_t address, uint8_t value);
		void WriteWordCPU(uint16_t address, uint16_t value);

		uint8_t ReadByteCPU(uint16_t address);
		uint16_t ReadWordCPU(uint16_t address);

		int cycleCount = 0;
	private:

		void CPUWritePPUReg(uint16_t address, uint8_t value);
		void OAMDump(uint8_t value);

		using MemComponent = std::map<uint16_t, uint8_t>;
		MemComponent cpuMemory;
		MemComponent ppuMemory;
		MemComponent attributeMemory;
		MemComponent cartridgeMemory;
	};
}