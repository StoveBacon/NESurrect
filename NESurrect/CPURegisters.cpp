#include "CPURegisters.h"

namespace cpu {
	void CPURegisters::SetBit(uint8_t mask, uint8_t value) {
		if (value == 0) {
			P = P & ~mask;
		} else {
			P = P | mask;
		}
	}
	void CPURegisters::SetIfZero(uint8_t value) {
		SetBit(ZeroMask, value == 0);
	}
	void CPURegisters::SetIfNegative(uint8_t value) {
		SetBit(NegativeMask, (value >> 7) == 1);
	}
	void CPURegisters::SetZero(uint8_t value) {
		SetBit(ZeroMask, value);
	}
	void CPURegisters::SetCarry(uint8_t value) {
		SetBit(CarryMask, value);
	}
	void CPURegisters::SetOverflow(uint8_t value) {
		SetBit(OverflowMask, value);
	}
	void CPURegisters::SetInterrupt(uint8_t value) {
		SetBit(InterruptDisMask, value);
	}
	void CPURegisters::SetDecimal(uint8_t value) {
		SetBit(DecimalMask, value);
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