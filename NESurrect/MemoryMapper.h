#pragma once
#include <cstdint>
#include <map>

namespace memory {
	typedef std::map<const uint16_t, uint8_t*> MemoryMap;

	class MemoryMapper {
	public:
		void AddMap(const uint16_t senderAddress, uint8_t *reciever) {
			maps[senderAddress] = reciever;
		}
		void Map(const uint16_t address, const uint8_t value) {
			*maps[address] = value;
		}
	private:
		MemoryMap maps;
	};
}