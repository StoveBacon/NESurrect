#include "CPURegisters.h"

namespace CPU {
	void CPURegisters::SetIfZero(const uint8_t& value) {
		P = P | ((value == 0) ? ZeroMask : 0U);
	}
	void CPURegisters::SetIfNegative(const uint8_t& value) {
		P = P | ((value & NegativeMask) > 0 ? NegativeMask : 0U);
	}
	void SetIfZeroAndNegative(const uint8_t& value, CPURegisters& registers) {
		registers.SetIfZero(value);
		registers.SetIfNegative(value);
	}
}