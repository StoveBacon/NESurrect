#include "Memory.h"

namespace mem {

	Memory::Memory() : mmr_(memory_, vram_, attributeMemory_) {
		// Todo replace this with smart pointers
		for (int i = 0; i < INTERNAL_RAM_SIZE; i++) {
			memory_.push_back(new MemoryValue);
		}

		// Mirror internal memory to the start of ppu register memory
		for (int i = INTERNAL_RAM_SIZE; i < REG_PPU_START; i++) {
			memory_.push_back(memory_[i % INTERNAL_RAM_SIZE]);
		}

		std::vector<MemoryValue*> mappedRegisters = mmr_.GetRegisters();
		for (int i = REG_PPU_START; i < REG_APU_IO_START; i++) {
			memory_.push_back(mappedRegisters[i % REG_PPU_SIZE]);
		}

		for (int i = REG_APU_IO_START; i < MEM_TOTAL_SIZE; i++) {
			memory_.push_back(new MemoryValue);
		}

	}

	Memory::~Memory()
	{
		for (int i = 0; i < MEM_TOTAL_SIZE; i++) {
			if (memory_[i] != nullptr) {
				delete memory_[i];
				memory_[i] = nullptr;
			}
		}
	}

	uint8_t Memory::readByte(uint16_t address) {
		return memory_[address]->get();
	}

	uint16_t Memory::readWord(uint16_t address) {
		// TODO: zero page wraparound
		uint16_t retval = readByte(address) << 8;
		retval = retval & readByte(address + 1);
		return retval;
	}

	void Memory::writeByte(uint16_t address, uint8_t value) {
		memory_[address]->set(value);
	}

	void Memory::writeWord(uint16_t address, uint16_t value) {
		// Little endian, write high byte first
		writeByte(address, (value & 0xFF00) >> 8);
		writeByte(address + 1, value & 0xFF);
	}
}