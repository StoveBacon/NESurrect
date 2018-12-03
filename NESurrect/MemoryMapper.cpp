#include "MemoryMapper.h"

namespace memory {
	MemoryMapper::~MemoryMapper() {
		while (PPUMemoryQueue.size() > 0) {
			PopPPUQueue();
		}
	}

	void MemoryMapper::LogCPUMemoryAccess(const uint16_t address, const uint8_t value) {
		// Validate the range on the access. PPU registers are at [2000, 2007] and [4014]
		if (address >= 0x2000 && address <= 0x2007) {
			const Message *message = new Message(address, value);
			PPUMemoryQueue.push(message);
		}
	}
	const Message const *MemoryMapper::NextPPUMessage() {
		return PPUMemoryQueue.front();
	}

	void MemoryMapper::PopPPUQueue() {
		if (PPUMemoryQueue.size() > 0) {
			delete PPUMemoryQueue.front();
			PPUMemoryQueue.pop();
		}
	}
}