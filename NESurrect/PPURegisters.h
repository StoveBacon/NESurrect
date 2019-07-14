#pragma once
#include <cstdint>
#include "MappedRegisters.h"

namespace mem {
	// These particular registers have unique logic on reads/writes that affect PPU registers
	class MappedRegisters;

	class BaseRegister : public MemoryValue {
	public:
		BaseRegister(MappedRegisters *mmr) { reg_ = mmr; }
		~BaseRegister() {}
	protected:
		MappedRegisters *reg_;
	};

	class StatusRegister : public BaseRegister {
	public:
		uint8_t get();
	};

	class OamDataRegister : public BaseRegister {
	public:
		void set(const uint8_t &val);
	};

	class DmaStartRegister : public BaseRegister {
	public:
		void set(const uint8_t &val);
	};

	// Scroll and internal address both use double writes, and share an 8 bit latch between the two.
	class DoubleWriteRegister : public BaseRegister {
	public:
		void set(const uint8_t &val);
	};

	// Handles reads and writes to VRAM
	class VramRWRegister : public BaseRegister {
	public:
		uint8_t get();
		void set(const uint8_t &val);
	};
}