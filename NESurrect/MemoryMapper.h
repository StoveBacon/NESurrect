#pragma once
#include <cstdint>
#include <queue>

namespace memory {
	struct Message {
	public:
		Message(uint16_t addr, uint8_t val) : address(addr), value(val) {}
	private:
		const uint16_t address;
		const uint8_t value;
	};

	class MemoryMapper {
	public:
		~MemoryMapper();
		std::queue<const Message*> PPUMemoryQueue;
		void LogCPUMemoryAccess(const uint16_t address, const uint8_t value);
		const Message const *NextPPUMessage();
		void PopPPUQueue();
	};
}