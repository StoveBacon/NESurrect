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
	inline uint8_t Read(const uint16_t& address) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		return data_[offsetAddress];	
	}

	inline uint16_t ReadWord(const uint16_t& address) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		uint16_t retval = Read(address);
		retval = retval << 8;
		retval | address == ZeroPageBoundary ? Read(0x00) : Read(address + 1);
		return retval;
	}

	inline void Write(const uint16_t& address, const uint8_t& data) {
		uint16_t offsetAddress = MapAddress(address, ranges...);
		data_[offsetAddress] = data;
	}

private:
	template <typename... Rest>
	inline uint16_t MapAddress(const uint16_t& address, const uint16_t& low, const uint16_t& high, const uint16_t& size, const Rest&... rest) {
		if (address >= low && address < high) {
			return (address % size) + low;
		}
		else {
			return MapAddress(address, rest...);
		}
	}

	inline uint16_t MapAddress(const uint16_t& address) {
		return address;
	}
	uint8_t ZeroPageBoundary = 0xFF;
	uint8_t data_[size] = { 0 };
};