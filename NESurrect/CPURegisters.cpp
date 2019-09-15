#include "CPURegisters.h"

void CPURegisters::setBit(uint8_t mask, uint8_t value) {
	if (value == 0) {
		P = P & ~mask;
	} else {
		P = P | mask;
	}
}
void CPURegisters::setIfZero(uint8_t value) {
	setBit(ZERO_MASK, value == 0);
}
void CPURegisters::setIfNegative(uint8_t value) {
	setBit(NEGATIVE_MASK, (value >> 7) == 1);
}
void CPURegisters::setZero(uint8_t value) {
	setBit(ZERO_MASK, value);
}
void CPURegisters::setCarry(uint8_t value) {
	setBit(CARRY_MASK, value);
}
void CPURegisters::setOverflow(uint8_t value) {
	setBit(OVERFLOW_MASK, value);
}
void CPURegisters::setInterrupt(uint8_t value) {
	setBit(INTERRUPT_DIS_MASK, value);
}
void CPURegisters::setDecimal(uint8_t value) {
	setBit(DECIMAL_MASK, value);
}
uint8_t CPURegisters::carry() {
	return ((P & CARRY_MASK) > 0 ? 1 : 0);
}
uint8_t CPURegisters::negative() {
	return ((P & NEGATIVE_MASK) > 0 ? 1 : 0);
}
uint8_t CPURegisters::overflow() {
	return ((P & OVERFLOW_MASK) > 0 ? 1 : 0);
}
uint8_t CPURegisters::interrupt() {
	return ((P & INTERRUPT_DIS_MASK) > 0 ? 1 : 0);
}
uint8_t CPURegisters::zero() {
	return ((P & ZERO_MASK) > 0 ? 1 : 0);
}
void setIfZeroAndNegative(const uint8_t& value, CPURegisters& registers) {
	registers.setIfZero(value);
	registers.setIfNegative(value);
}