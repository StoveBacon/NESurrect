#pragma once
#include <cstdint>

namespace CPU {
	class CPURegisters {
	public:
		void SetIfZero(const uint8_t& value);
		void SetIfNegative(const uint8_t& value);

		uint8_t A;
		uint8_t X;
		uint8_t Y;
		uint16_t PC;
		uint8_t S;
		uint8_t P;
	private:
		static constexpr uint8_t CarryMask = 0b0000;
		static constexpr uint8_t ZeroMask = 0b0010;
		static constexpr uint8_t InterruptDisMask = 0b0100;
		static constexpr uint8_t DecimalMask = 0b1000;
		static constexpr uint8_t OverflowMask = 0b01000000;
		static constexpr uint8_t NegativeMask = 0b10000000;
	};

	void SetIfZeroAndNegative(const uint8_t& value, CPURegisters& registers);
}