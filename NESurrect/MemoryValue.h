#pragma once
#include <cstdint>
#include "Constants.h"

namespace mem {

	// Because some reads and writes affect other parts of memory,
	// a base get() method is used instead of conditional checks

	// Base class used for almost all memory values
	class MemoryValue {
	public:
		MemoryValue() : value_(0) {}
		virtual ~MemoryValue() = default;
		virtual uint8_t get() { return value_; }
		uint8_t value() { return value_;  }
		virtual void set(const uint8_t &val) { value_ = val; }

		void increment(uint8_t amount = 1U);

		// Helper function for handling bits from a register
		uint16_t getFlag(uint16_t mask);
		void setBits(bool setOrClear, uint8_t mask);

	protected:
		uint8_t value_;
	};
}
