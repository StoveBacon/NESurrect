#include "Memory.h"

namespace mem {
	// Mirror the address to the appropriate location
	uint16_t Memory::GetAbsoluteAddress(uint16_t address) {
		if (address >= 0x1000 && address <= 0x3FFF) {
			return address % 0x800;
		}
		else if (address <= 0x3FFF) {
			return (address % 0x08) + 0x2000;
		} else {
			return address;
		}
	}

	void Memory::IncrementAddressLatch() {
		unsigned short incMode = memory[ppu::PPUCtrl];
		incMode = incMode & ppu::IncMode;
		memory[ppu::PPUAddress] += incMode ? 32 : 1;
	}

	void Memory::OAMDump(uint8_t address) {
		// Dumps the page that was written in
		address = address << 8;

		// Address serves as a page offset of memory to dump into the OAM
		for (uint16_t i = 0; i < 256; i++) {
			attributeMemory[i] = memory[i + address];
		}
	}

	uint8_t Memory::ReadByte(uint16_t address) {
		address = GetAbsoluteAddress(address);

		if (address == ppu::PPUStatus) {
			memory[ppu::PPUAddress] = 0;
		}
		else if (address == ppu::PPUData) {

			uint16_t tempAddr = memory[ppu::PPUAddress];
			uint8_t tempBuffer = vramBuffer;
			vramBuffer = VRAM[tempAddr];

			IncrementAddressLatch();

			return tempBuffer;
		}

		return memory[address];
	}

	uint16_t Memory::ReadWord(uint16_t address) {
		// TODO: Zero page wraparound
		uint16_t retval = ReadByte(address) << 8;
		retval = retval & ReadByte(address + 1);
		return retval;
	}

	void Memory::WriteByte(uint16_t address, uint8_t value) {
		address = GetAbsoluteAddress(address);

		// Handle memory mapped registers
		switch (address) {

		case ppu::OAMData:
			attributeMemory[memory[ppu::OAMAddress]] = value;
			memory[ppu::OAMAddress]++;
			break;

		case ppu::PPUAddress:
			memory[ppu::PPUAddress] = (memory[ppu::PPUAddress] << 8) + value;
			break;

		case ppu::PPUData:
			VRAM[memory[ppu::PPUAddress]] = value;
			IncrementAddressLatch();
			break;

		case ppu::PPUScroll:
			memory[address] = (memory[address] << 8) + value;
			break;

		case ppu::OAMDump:
			OAMDump(value);
			break;
		}

		memory[address] = value;
	}

	void Memory::WriteWord(uint16_t address, uint16_t value) {
		// Little endian, write high byte first
		WriteByte(address, (value & 0xFF00) >> 8);
		WriteByte(address + 1, value & 0xFF);
	}

	uint8_t Memory::ReadPPUReg(uint16_t address) {
		address = GetAbsoluteAddress(address);
		return memory[address];
	}
}

/*
namespace mem {
	void Memory::WriteByte(uint16_t address, uint8_t value) {
		cycleCount++;

		// Check for mirrored values first
		if (address < 0x2000) {
			address = address % 0x800;
		} else if (address < 0x3FFF) {
			address = (address % 0x08) + 0x2000;
			CPUWritePPUReg(address, value);
		} else if (address == 0x4014) {
			OAMDump(value);
		}

		memory[address] = value;
	}

	// Little endian, write high byte first
	void Memory::WriteWord(uint16_t address, uint16_t value) {
		WriteByte(address, value >> 8);
		WriteByte(address + 1, value & 0xFF);
	}

	uint8_t Memory::ReadByte(uint16_t address) {
		cycleCount++;
		if (address < 0x2000) {
			address = address % 0x800;

			// Reading PPU scroll resets it
			if (address == ppu::PPUScroll) {
				uint8_t retval = memory[address];
				memory[address] = 0;
				return retval;
			}
		} else if (address < 0x3FFF) {
			address = (address % 0x08) + 0x2000;
		}
		return memory[address];
	}

	uint16_t Memory::ReadWord(uint16_t address) {
		uint16_t retval = ReadByte(address) << 8;
		retval = retval & ReadByte(address + 1);
		return retval;
	}

	// Takes in the address in CPU space to write to a PPU register
	void Memory::CPUWritePPUReg(uint16_t address, uint8_t value) {
		switch (address) {
		// Do nothing special here for now
		case ppu::PPUCtrl: case ppu::PPUMask: case ppu::PPUStatus: case ppu::OAMAddress:
			memory[address] = value;
			break;

		case ppu::OAMData:
			attributeMemory[memory[ppu::OAMAddress]] = value;
			memory[ppu::OAMAddress]++;
			break;

		// Handle registers that double write
		case ppu::PPUScroll: case ppu::PPUAddress:
			uint8_t operand = memory[address];
			if (operand == 0) {
				value = value << 8;
			}
			operand = operand & value;
			memory[address] = operand;
			break;
		}
	}

	uint8_t Memory::ReadPPUReg(uint16_t address) {
		return memory[address];
	}

	void Memory::WritePPUReg(uint16_t address, uint8_t value) {
		memory[address] = value;
	}

	void Memory::OAMDump(uint8_t address) {
		// Dumps the page that was written in
		address = address << 8;

		// Address serves as a page offset of memory to dump into the OAM
		for (int i = 0; i < 256; i++) {
			attributeMemory[i] = memory[i + address];
		}
		// 256 reads/writes technically performed during this operation
		cycleCount += 512;
	}
}*/