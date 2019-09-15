#include "MemoryValue.h"

namespace mem {
	uint16_t MemoryValue::getFlag(uint16_t mask) {
		uint8_t tempVal = value_;

		// Strip off rightmost extra data
		while ((mask & 0b01) == 0)
		{
			mask = mask >> 1;
			tempVal = tempVal >> 1;
		}

		return mask & tempVal;
	}

	void MemoryValue::setBits(bool setOrClear, uint8_t mask) {
		value_ = setOrClear ? (value_ | mask) : (value_ & (~mask));
	}

	void MemoryValue::increment(uint8_t amount) {
		value_ += amount;
	}
}