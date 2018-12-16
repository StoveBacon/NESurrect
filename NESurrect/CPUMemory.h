#pragma once
#include "Memory.h"
#include "MemoryMapper.h"

namespace memory {


	class CPUMemory : public Memory<MemSize, RAMMirrorLow, RAMMirrorHigh, RAMMirrorSize, PPUMirrorLow, PPUMirrorHigh, PPUMirrorSize> {
	public:
		CPUMemory(MemoryMapper *map) : mapper(map) {}

		void Write(const uint16_t address, const uint8_t data) {
			cycles++;
			Memory::Write(address, data);
			mapper->LogCPUMemoryAccess(offsetAddress, data);
		}
		uint8_t Read(const uint16_t address) {
			cycles++;
			uint8_t data = Memory::Read(address);
			mapper->LogCPUMemoryAccess(offsetAddress, data);
			return data;
		}

		// Cycles are tracked in order to catch up the other components of the system while maintaining accuracy
		// They will be reset every time an instruction is completed
		int cycles = 0;

	protected:
		MemoryMapper *mapper;
	};
}
