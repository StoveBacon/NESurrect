#include "Memory.h"

namespace mem {
	void Memory::WriteByteCPU(uint16_t address, uint8_t value) {
		// Check for mirrored values first
		if (address < 0x2000) {
			address = address % 0x800;
		} else if (address < 0x3FFF) {
			address = (address % 0x08) + 0x2000;
			CPUWritePPUReg(address, value);
		} else if (address == 0x4014) {
			OAMDump(value);
		}

		cpuMemory[address] = value;
		cycleCount++;
	}

	// Little endian, write high byte first
	void Memory::WriteWordCPU(uint16_t address, uint16_t value) {
		WriteByteCPU(address, value >> 8);
		WriteByteCPU(address + 1, value & 0xFF);
	}

	uint8_t Memory::ReadByteCPU(uint16_t address) {
		if (address < 0x2000) {
			address = address % 0x800;
		} else if (address < 0x3FFF) {
			address = (address % 0x08) + 0x2000;
		}
		return cpuMemory[address];
	}

	uint16_t Memory::ReadWordCPU(uint16_t address) {
		uint16_t retval = ReadByteCPU(address) << 8;
		retval = retval & ReadByteCPU(address + 1);
		return retval;
	}

	// Takes in the address in CPU space to write to a PPU register
	void Memory::CPUWritePPUReg(uint16_t address, uint8_t value) {
		switch (address) {
		// Do nothing special here for now
		case ppu::PPUCtrl: case ppu::PPUMask: case ppu::PPUStatus: case ppu::OAMAddress:
			cpuMemory[address] = value;
			break;

		case ppu::OAMData:
			attributeMemory[cpuMemory[ppu::OAMAddress]] = value;
			cpuMemory[ppu::OAMAddress]++;
			break;

		// Handle registers that double write
		case ppu::PPUScroll: case ppu::PPUAddress:
			uint8_t operand = cpuMemory[address];
			if (operand == 0) {
				value = value << 8;
			}
			operand = operand & value;
			cpuMemory[address] = operand;
			break;
		}
	}

	void Memory::OAMDump(uint8_t address) {
		// Dumps the page that was written in
		address = address << 8;

		// Address serves as a page offset of memory to dump into the OAM
		for (int i = 0; i < 256; i++) {
			attributeMemory[i] = cpuMemory[i + address];
		}
		// 256 reads/writes technically performed during this operation
		cycleCount += 512;
	}
}