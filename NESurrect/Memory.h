#pragma once
#include <cstdint>

/* 
 * This class emulates memory, and is capable of mirroring ranges by
 * providing the ranges in the order { low, high, size } as template parameters.
 * Otherwise, there will be no mirroring.
 */

template <int size, uint16_t... ranges>
class Memory {
public:
	uint8_t Read(const uint16_t address) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		return data_[offsetAddress];	
	}

	uint16_t ReadWord(const uint16_t address) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		uint16_t retval = Read(offsetAddress);
		retval = retval << 8;
		retval = retval | (offsetAddress == ZeroPageBoundary) ? Read(0x00) : Read(offsetAddress + 1);
		return retval;
	}

	void Write(const uint16_t address, const uint8_t data) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		data_[offsetAddress] = data;
	}
	void WriteWord(const uint16_t address, const uint16_t data) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		// 6502 is little-endian, so bytes have to be written backwards
		data_[offsetAddress] = (data & 0xFF00) >> 8;
		data_[offsetAddress - 1] = (data & 0x00FF);
	}
private:
	template <typename... Rest>
	uint16_t MapAddress(const uint16_t address, const uint16_t low, const uint16_t high, const uint16_t size, const Rest... rest) {
		if (address >= low && address < high) {
			return (address % size) + low;
		}
		else {
			return MapAddress(address, rest...);
		}
	}

	uint16_t MapAddress(const uint16_t address) {
		return address;
	}
	uint8_t ZeroPageBoundary = 0xFF;
	uint8_t data_[size] = { 0 };
};