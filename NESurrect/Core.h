#pragma once
#include "CPURegisters.h"
#include "CPUMemory.h"

namespace CPU {
	class Core {
	public:
		void ExecuteInstruction();
	private:
		CPURegisters reg_;
		CPUMemory mem_;

		// Addressing modes
		uint8_t ZeroPageX();
		uint8_t ZeroPageY();
		uint8_t ZeroPage();
		uint8_t Immediate();
		uint8_t Absolute();
		uint8_t IndirectY();
		uint8_t IndirectX();
		uint8_t AbsoluteX();
		uint8_t AbsoluteY();
		uint8_t Accumulator();

		// Addressing operations
		void ORA(uint8_t value);
		void AND(uint8_t value);
		void EOR(uint8_t value);
		void ADC(uint8_t value);
		void STA(uint8_t value);
		void LDA(uint8_t value);
		void CMP(uint8_t value);
		void SBC(uint8_t value);
		void ASL(uint8_t value);
		void ROL(uint8_t value);
		void LSR(uint8_t value);
		void ROR(uint8_t value);
		void STX(uint8_t value);
		void LDX(uint8_t value);
		void DEC(uint8_t value);
		void INC(uint8_t value);
		void BIT(uint8_t value);
		void JMP(uint8_t value);
		void STY(uint8_t value);
		void LDY(uint8_t value);
		void CPY(uint8_t value);
		void CPX(uint8_t value);

		// Single byte operations
		void JMPAbs();
		void JSRAbs();
		void BPL();
		void BMI();
		void BVC();
		void BVS();
		void BCC();
		void BCS();
		void BNE();
		void BEQ();
		void BRK();
		void RTI();
		void RTS();
		void PHP();
		void PLP();
		void PHA();
		void PLA();
		void DEY();
		void TAY();
		void INY();
		void INX();
		void CLC();
		void SEC();
		void CLI();
		void SEI();
		void TYA();
		void CLV();
		void CLD();
		void SED();
		void TXA();
		void TXS();
		void TAX();
		void TSX();
		void DEX();
		void NOP();
	};
}