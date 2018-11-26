#pragma once
#include <cstdint>
#include <bitset>

namespace cpu {
	static constexpr uint16_t StackOffset = 0x100;
	class CPURegisters {
	public:
		void SetIfZero(uint8_t value);
		void SetIfNegative(uint8_t value);
		void SetZero(uint8_t value);
		void SetCarry(uint8_t value);
		void SetOverflow(uint8_t value);
		void SetInterrupt(uint8_t value);
		void SetDecimal(uint8_t value);
		uint8_t Carry();
		uint8_t Negative();
		uint8_t Overflow();
		uint8_t Zero();

		uint8_t A;
		uint8_t X;
		uint8_t Y;
		uint16_t PC;
		uint8_t S;
		uint8_t P;

	private:
		void SetBit(uint8_t mask, uint8_t value);

		static constexpr uint8_t CarryMask = 0b0001;
		static constexpr uint8_t ZeroMask = 0b0010;
		static constexpr uint8_t InterruptDisMask = 0b0100;
		static constexpr uint8_t DecimalMask = 0b1000;
		static constexpr uint8_t OverflowMask = 0b01000000;
		static constexpr uint8_t NegativeMask = 0b10000000;
	};

	void SetIfZeroAndNegative(const uint8_t& value, CPURegisters& registers);
}