#include "CPURegisters.h"

namespace CPU {
	void CPURegisters::SetIfZero(uint8_t value) {
		P = P | ((value == 0) ? ZeroMask : 0U);
	}
	void CPURegisters::SetIfNegative(uint8_t value) {
		P = P | ((value & NegativeMask) > 0 ? NegativeMask : 0U);
	}
	void CPURegisters::SetZero(uint8_t value) {
		P = P | ((value > 0)) ? ZeroMask : 0U;
	}
	void CPURegisters::SetCarry(uint8_t value) {
		P = P | ((value > 0)) ? CarryMask : 0U;
	}
	void CPURegisters::SetOverflow(uint8_t value) {
		P = P | ((value > 0)) ? OverflowMask : 0U;
	}
	void CPURegisters::SetInterrupt(uint8_t value) {
		P = P | ((value > 0)) ? InterruptDisMask : 0U;
	}
	uint8_t CPURegisters::Carry() {
		return ((P & CarryMask) > 0);
	}
	uint8_t CPURegisters::Negative() {
		return ((P & NegativeMask) > 0);
	}
	uint8_t CPURegisters::Overflow() {
		return ((P & OverflowMask) > 0);
	}
	uint8_t CPURegisters::Zero() {
		return ((P & ZeroMask) > 0);
	}
	void SetIfZeroAndNegative(const uint8_t& value, CPURegisters& registers) {
		registers.SetIfZero(value);
		registers.SetIfNegative(value);
	}
}