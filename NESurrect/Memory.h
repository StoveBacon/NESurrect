#pragma once
#include <unordered_map>
#include <fstream>
#include "MappedRegisters.h"
#include "MemoryValue.h"
#include "Constants.h"
#include "Mapper.h"

namespace mem {
	class MappedRegister;

	// The memory is actually divided into 3 parts but they're so tightly coupled
	// in the hardware that it is much easier to just group them all together

	class Memory {
	public:
		Memory();
		~Memory();

		void writeByte(uint16_t address, uint8_t value);
		void writeWord(uint16_t address, uint16_t value);

		uint8_t peekVram(uint16_t address) { return vram_[address]->value(); }
		uint8_t readByte(uint16_t address);
		uint16_t readWord(uint16_t address);

	private:
		using MemComponent = std::vector<MemoryValue*>;
		MemComponent memory_;
		MemComponent vram_;
		MemComponent attributeMemory_;
		MemComponent cartridgeMemory_;

		MappedRegisters mmr_;

		Mapper mapper_;
	};
}