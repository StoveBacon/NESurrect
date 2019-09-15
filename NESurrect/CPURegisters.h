#pragma once
#include <cstdint>
#include <bitset>

static constexpr uint16_t StackOffset = 0x100;
class CPURegisters {
public:
	void setIfZero(uint8_t value);
	void setIfNegative(uint8_t value);
	void setZero(uint8_t value);
	void setCarry(uint8_t value);
	void setOverflow(uint8_t value);
	void setInterrupt(uint8_t value);
	void setDecimal(uint8_t value);
	uint8_t carry();
	uint8_t negative();
	uint8_t overflow();
	uint8_t zero();
	uint8_t interrupt();

	uint8_t A;
	uint8_t X;
	uint8_t Y;
	uint16_t startPC;
	uint16_t PC;
	uint8_t S;
	uint8_t P;

private:
	void setBit(uint8_t mask, uint8_t value);

	static constexpr uint8_t CARRY_MASK = 0b0001;
	static constexpr uint8_t ZERO_MASK = 0b0010;
	static constexpr uint8_t INTERRUPT_DIS_MASK = 0b0100;
	static constexpr uint8_t DECIMAL_MASK = 0b1000;
	static constexpr uint8_t OVERFLOW_MASK = 0b01000000;
	static constexpr uint8_t NEGATIVE_MASK = 0b10000000;
};

void setIfZeroAndNegative(const uint8_t& value, CPURegisters& registers);
