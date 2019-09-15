#pragma once
#include <vector>
#include "MemoryValue.h"
#include "DataLatch.h"

// Wrap up all the mapping and special logic involved in certain PPU mapped registers
namespace mem {
	using MemComponent = const std::vector<MemoryValue*>*;

	class MappedRegisters {
	public:
		MappedRegisters(MemComponent memory, MemComponent vram, MemComponent oam);
		~MappedRegisters() {}

		std::vector<MemoryValue*> registers;
		std::vector<MemoryValue*> GetRegisters();

		void IncrementVramAddress();
		uint16_t vramAddress;
		DataLatch latch;

		MemComponent memory;
		MemComponent vram;
		MemComponent oam;
	};

	// These particular registers have unique logic on reads/writes that affect PPU registers
	class BaseRegister : public MemoryValue {
	public:
		BaseRegister(MappedRegisters *mmr) { reg_ = mmr; }
		~BaseRegister() = default;
	protected:
		MappedRegisters *reg_;
	};

	class StatusRegister : public BaseRegister {
	public:
		StatusRegister(MappedRegisters *mmr) : BaseRegister(mmr) {}
		uint8_t get();
	};

	class OamDataRegister : public BaseRegister {
	public:
		OamDataRegister(MappedRegisters *mmr) : BaseRegister(mmr) {}
		void set(const uint8_t &val);
	};

	class DmaStartRegister : public BaseRegister {
	public:
		DmaStartRegister(MappedRegisters *mmr) : BaseRegister(mmr) {}
		void set(const uint8_t &val);
	};

	// Scroll and internal address both use double writes, and share an 8 bit latch between the two.
	class DoubleWriteRegister : public BaseRegister {
	public:
		DoubleWriteRegister(MappedRegisters *mmr) : BaseRegister(mmr) {}
		void set(const uint8_t &val);
	};

	// Handles reads and writes to VRAM
	class VramRWRegister : public BaseRegister {
	public:
		VramRWRegister(MappedRegisters *mmr) : BaseRegister(mmr) {}
		uint8_t get();
		void set(const uint8_t &val);
	};
}