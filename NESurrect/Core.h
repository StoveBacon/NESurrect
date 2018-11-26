#pragma once
#include "CPURegisters.h"
#include "CPUMemory.h"

namespace cpu {
	struct Instruction {
		Instruction() : value(0), address(0), isAccumulator(false) {}
		uint8_t opcode;
		uint8_t value;
		uint16_t address;
		bool isAccumulator;
	};

	class Core {
	public:
		Core(memory::CPUMemory *mem);
		void Reset();
		void ExecuteInstruction();

		
	private:
		CPURegisters reg_;
		memory::CPUMemory *mem_;

		// Addressing modes
		const Instruction ZeroPageX(Instruction& ins);
		const Instruction ZeroPageY(Instruction& ins);
		const Instruction ZeroPage(Instruction& ins);
		const Instruction Immediate(Instruction& ins);
		const Instruction Absolute(Instruction& ins);
		const Instruction IndirectY(Instruction& ins);
		const Instruction IndirectX(Instruction& ins);
		const Instruction AbsoluteX(Instruction& ins);
		const Instruction AbsoluteY(Instruction& ins);
		const Instruction Accumulator(Instruction& ins);

		// Addressing operations
		void ORA(const Instruction& ins);
		void AND(const Instruction& ins);
		void EOR(const Instruction& ins);
		void ADC(const Instruction& ins);
		void STA(const Instruction& ins);
		void LDA(const Instruction& ins);
		void CMP(const Instruction& ins);
		void SBC(const Instruction& ins);
		void ASL(const Instruction& ins);
		void ROL(const Instruction& ins);
		void LSR(const Instruction& ins);
		void ROR(const Instruction& ins);
		void STX(const Instruction& ins);
		void LDX(const Instruction& ins);
		void DEC(const Instruction& ins);
		void INC(const Instruction& ins);
		void BIT(const Instruction& ins);
		void JMP(const Instruction& ins);
		void STY(const Instruction& ins);
		void LDY(const Instruction& ins);
		void CPY(const Instruction& ins);
		void CPX(const Instruction& ins);

		// Single byte operations
		void JMP();
		void JSR();
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

		uint8_t Relative(uint8_t address);
		void Compare(uint8_t a, uint8_t b);
		void BranchIfClear(uint8_t value);
		void BranchIfSet(uint8_t value);
	};
}
