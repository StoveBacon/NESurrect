#include "Core.h"

namespace CPU {
	Core::Core() {
		Reset();
	}
	void Core::Reset() {
		constexpr uint16_t ResetVector = 0xFFFC;
		constexpr uint8_t StatusDefault = 0x24;
		constexpr uint8_t SPDefault = 0xFD;
		reg_.PC = mem_.ReadWord(ResetVector);
		reg_.P = StatusDefault;
		reg_.S = SPDefault;
	}
	void Core::ExecuteInstruction() {
		Instruction ins;
		ins.opcode = mem_.Read(reg_.PC);
		reg_.PC++;
		switch (ins.opcode) {
		case 0x01: ORA(IndirectX(ins)); break;
		case 0x05: ORA(ZeroPage(ins)); break;
		case 0x09: ORA(Immediate(ins)); break;
		case 0x0D: ORA(Absolute(ins)); break;
		case 0x11: ORA(IndirectY(ins)); break;
		case 0x15: ORA(ZeroPageX(ins)); break;
		case 0x19: ORA(AbsoluteY(ins)); break;
		case 0x1D: ORA(AbsoluteX(ins)); break;

		case 0x21: AND(IndirectX(ins)); break;
		case 0x25: AND(ZeroPage(ins)); break;
		case 0x29: AND(Immediate(ins)); break;
		case 0x2D: AND(Absolute(ins)); break;
		case 0x31: AND(IndirectY(ins)); break;
		case 0x35: AND(ZeroPageX(ins)); break;
		case 0x39: AND(AbsoluteY(ins)); break;
		case 0x3D: AND(AbsoluteX(ins)); break;

		case 0x41: EOR(IndirectX(ins)); break;
		case 0x45: EOR(ZeroPage(ins)); break;
		case 0x49: EOR(Immediate(ins)); break;
		case 0x4D: EOR(Absolute(ins)); break;
		case 0x51: EOR(IndirectY(ins)); break;
		case 0x55: EOR(ZeroPageX(ins)); break;
		case 0x59: EOR(AbsoluteY(ins)); break;
		case 0x5D: EOR(AbsoluteX(ins)); break;

		case 0x61: ADC(IndirectX(ins)); break;
		case 0x65: ADC(ZeroPage(ins)); break;
		case 0x69: ADC(Immediate(ins)); break;
		case 0x6D: ADC(Absolute(ins)); break;
		case 0x71: ADC(IndirectY(ins)); break;
		case 0x75: ADC(ZeroPageX(ins)); break;
		case 0x79: ADC(AbsoluteY(ins)); break;
		case 0x7D: ADC(AbsoluteX(ins)); break;

		case 0x81: STA(IndirectX(ins)); break;
		case 0x85: STA(ZeroPage(ins)); break;
		// case 0x89: STA(Immediate(ins)); break; Illegal
		case 0x8D: STA(Absolute(ins)); break;
		case 0x91: STA(IndirectY(ins)); break;
		case 0x95: STA(ZeroPageX(ins)); break;
		case 0x99: STA(AbsoluteY(ins)); break;
		case 0x9D: STA(AbsoluteX(ins)); break;

		case 0xA1: LDA(IndirectX(ins)); break;
		case 0xA5: LDA(ZeroPage(ins)); break;
		case 0xA9: LDA(Immediate(ins)); break;
		case 0xAD: LDA(Absolute(ins)); break;
		case 0xB1: LDA(IndirectY(ins)); break;
		case 0xB5: LDA(ZeroPageX(ins)); break;
		case 0xB9: LDA(AbsoluteY(ins)); break;
		case 0xBD: LDA(AbsoluteX(ins)); break;

		case 0xC1: CMP(IndirectX(ins)); break;
		case 0xC5: CMP(ZeroPage(ins)); break;
		case 0xC9: CMP(Immediate(ins)); break;
		case 0xCD: CMP(Absolute(ins)); break;
		case 0xD1: CMP(IndirectY(ins)); break;
		case 0xD5: CMP(ZeroPageX(ins)); break;
		case 0xD9: CMP(AbsoluteY(ins)); break;
		case 0xDD: CMP(AbsoluteX(ins)); break;

		case 0xE1: SBC(IndirectX(ins)); break;
		case 0xE5: SBC(ZeroPage(ins)); break;
		case 0xE9: SBC(Immediate(ins)); break;
		case 0xED: SBC(Absolute(ins)); break;
		case 0xF1: SBC(IndirectY(ins)); break;
		case 0xF5: SBC(ZeroPageX(ins)); break;
		case 0xF9: SBC(AbsoluteY(ins)); break;
		case 0xFD: SBC(AbsoluteX(ins)); break;

		// case 0x02: ASL(Immediate(ins)); break; Illegal
		case 0x06: ASL(ZeroPage(ins)); break;
		case 0x0A: ASL(Accumulator(ins)); break;
		case 0x0E: ASL(Absolute(ins)); break;
		case 0x16: ASL(ZeroPageX(ins)); break;
		case 0x1E: ASL(AbsoluteX(ins)); break;

		// case 0x22: ROL(Immediate(ins)); break; Illegal
		case 0x26: ROL(ZeroPage(ins)); break;
		case 0x2A: ROL(Accumulator(ins)); break;
		case 0x2E: ROL(Absolute(ins)); break;
		case 0x36: ROL(ZeroPageX(ins)); break;
		case 0x3E: ROL(AbsoluteX(ins)); break;

		// case 0x42: LSR(Immediate(ins)); break; Illegal
		case 0x46: LSR(ZeroPage(ins)); break;
		case 0x4A: LSR(Accumulator(ins)); break;
		case 0x4E: LSR(Absolute(ins)); break;
		case 0x56: LSR(ZeroPageX(ins)); break;
		case 0x5E: LSR(AbsoluteX(ins)); break;

		// case 0x62: ROR(Immediate(ins)); break; Illegal
		case 0x66: ROR(ZeroPage(ins)); break;
		case 0x6A: ROR(Accumulator(ins)); break;
		case 0x6E: ROR(Absolute(ins)); break;
		case 0x76: ROR(ZeroPageX(ins)); break;
		case 0x7E: ROR(AbsoluteX(ins)); break;

		// case 0x82: STX(Immediate(ins)); break; Illegal
		case 0x86: STX(ZeroPage(ins)); break;
		case 0x8E: STX(Absolute(ins)); break;
		case 0x96: STX(ZeroPageY(ins)); break;
		// case 0x9E: STX(IndirectY(ins)); break; Illegal

		case 0xA2: LDX(Immediate(ins)); break;
		case 0xA6: LDX(ZeroPage(ins)); break;
		case 0xAE: LDX(Absolute(ins)); break;
		case 0xB6: LDX(ZeroPageY(ins)); break;
		case 0xBE: LDX(AbsoluteY(ins)); break;

		// case 0xC2: DEC(Immediate(ins)); break; Illegal
		case 0xC6: DEC(ZeroPage(ins)); break;
		case 0xCE: DEC(Absolute(ins)); break;
		case 0xD6: DEC(ZeroPageX(ins)); break;
		case 0xDE: DEC(AbsoluteX(ins)); break;

		// case 0xE2: INC(Immediate(ins)); break; Illegal
		case 0xE6: INC(ZeroPage(ins)); break;
		case 0xEE: INC(Absolute(ins)); break;
		case 0xF6: INC(ZeroPageX(ins)); break;
		case 0xFE: INC(AbsoluteX(ins)); break;

		case 0x24: BIT(ZeroPage(ins)); break;
		case 0x2C: BIT(Absolute(ins)); break;

		case 0x4C: JMP(Absolute(ins)); break;

		case 0x84: STY(ZeroPage(ins)); break;
		case 0x8C: STY(Absolute(ins)); break;
		case 0x94: STY(ZeroPageX(ins)); break;

		case 0xA0: LDY(Immediate(ins)); break;
		case 0xA4: LDY(ZeroPage(ins)); break;
		case 0xAC: LDY(Absolute(ins)); break;
		case 0xB4: LDY(ZeroPageX(ins)); break;
		case 0xBC: LDY(AbsoluteX(ins)); break;

		case 0xC0: CPY(Immediate(ins)); break;
		case 0xC4: CPY(ZeroPage(ins)); break;
		case 0xCC: CPY(Absolute(ins)); break;

		case 0xE0: CPX(Immediate(ins)); break;
		case 0xE4: CPX(ZeroPage(ins)); break;
		case 0xEC: CPX(Absolute(ins)); break;

		case 0x6C: JMP(); break;
		case 0x20: JSR(); break;
		case 0x10: BPL(); break;
		case 0x30: BMI(); break;
		case 0x50: BVC(); break;
		case 0x70: BVS(); break;
		case 0x90: BCC(); break;
		case 0xB0: BCS(); break;
		case 0xD0: BNE(); break;
		case 0xF0: BEQ(); break;
		case 0x00: BRK(); break;
		case 0x40: RTI(); break;
		case 0x60: RTS(); break;
		case 0x08: PHP(); break;
		case 0x28: PLP(); break;
		case 0x48: PHA(); break;
		case 0x68: PLA(); break;
		case 0x88: DEY(); break;
		case 0xA8: TAY(); break;
		case 0xC8: INY(); break;
		case 0xE8: INX(); break;
		case 0x18: CLC(); break;
		case 0x38: SEC(); break;
		case 0x58: CLI(); break;
		case 0x78: SEI(); break;
		case 0x98: TYA(); break;
		case 0xB8: CLV(); break;
		case 0xD8: CLD(); break;
		case 0xF8: SED(); break;
		case 0x8A: TXA(); break;
		case 0x9A: TXS(); break;
		case 0xAA: TAX(); break;
		case 0xBA: TSX(); break;
		case 0xCA: DEX(); break;
		case 0xEA: NOP(); break;
		default: break;
		}
	}

	void Core::ORA(const Instruction& ins) {
		reg_.A = reg_.A | ins.value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::AND(const Instruction& ins) {
		reg_.A = reg_.A & ins.value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::EOR(const Instruction& ins) {
		reg_.A = reg_.A ^ ins.value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::ADC(const Instruction& ins) {
		uint8_t result = reg_.A + ins.value + reg_.Carry();
		SetIfZeroAndNegative(result, reg_);
		reg_.SetOverflow(((ins.value & 0x80) == (reg_.A & 0x80)) && ((result & 0x80) != (reg_.A & 0x80)));
		reg_.SetCarry(result < reg_.A);
		reg_.A = result;
	}
	void Core::STA(const Instruction& ins) {
		mem_.Write(ins.address, reg_.A);
	}
	void Core::LDA(const Instruction& ins) {
		reg_.A = ins.value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::CMP(const Instruction& ins) {
		Compare(reg_.A, ins.value);
	}
	void Core::SBC(const Instruction& ins) {
		Instruction temp = ins;
		temp.value ^= 0xFF;
		ADC(temp);
	}
	void Core::ASL(const Instruction& ins) {
		if (ins.isAccumulator) {
			reg_.SetCarry(reg_.A & 0x80);
			reg_.A = reg_.A << 1;
			SetIfZeroAndNegative(reg_.A, reg_);
		} else {
			uint8_t shifted = ins.value << 1;
			reg_.SetCarry(ins.value & 0x80);
			mem_.Write(ins.address, shifted);
			SetIfZeroAndNegative(shifted, reg_);
		}
	}
	void Core::ROL(const Instruction& ins) {
		if (ins.isAccumulator) {
			uint8_t shifted = (reg_.A << 1) | reg_.Carry();
			reg_.SetCarry(reg_.A & 0x80);
			reg_.A = shifted;
			SetIfZeroAndNegative(shifted, reg_);
		} else {
			uint8_t shifted = (ins.value << 1) | reg_.Carry();
			reg_.SetCarry(ins.value & 0x80);
			mem_.Write(ins.address, shifted);
			SetIfZeroAndNegative(shifted, reg_);
		}
	}
	void Core::LSR(const Instruction& ins) {
		if (ins.isAccumulator) {
			reg_.SetCarry(reg_.A & 0x01);
			reg_.A = reg_.A >> 1;
			SetIfZeroAndNegative(reg_.A, reg_);
		} else {
			uint8_t shifted = ins.value >> 1;
			reg_.SetCarry(ins.value & 0x01);
			mem_.Write(ins.address, shifted);
			SetIfZeroAndNegative(shifted, reg_);
		}
	}
	void Core::ROR(const Instruction& ins) {
		if (ins.isAccumulator) {
			uint8_t shifted = (reg_.A >> 1) | (reg_.Carry() << 7);
			reg_.SetCarry(reg_.A & 0x01);
			reg_.A = shifted;
			SetIfZeroAndNegative(reg_.A, reg_);
		} else {
			uint8_t shifted = (ins.value >> 1) | (reg_.Carry() << 7);
			reg_.SetCarry(ins.value & 0x01);
			mem_.Write(ins.address, shifted);
			SetIfZeroAndNegative(shifted, reg_);
		}
	}
	void Core::STX(const Instruction& ins) {
		mem_.Write(ins.address, reg_.X);
	}
	void Core::LDX(const Instruction& ins) {
		reg_.X = ins.value;
		SetIfZeroAndNegative(reg_.X, reg_);
	}
	void Core::DEC(const Instruction& ins) {
		mem_.Write(ins.address, ins.value - 1);
		SetIfZeroAndNegative(ins.value - 1, reg_);
	}
	void Core::INC(const Instruction& ins) {
		mem_.Write(ins.address, ins.value + 1);
		SetIfZeroAndNegative(ins.value + 1, reg_);
	}
	void Core::BIT(const Instruction& ins) {
		reg_.SetIfZero(reg_.A & ins.value);
		reg_.SetIfNegative(ins.value);
		reg_.SetOverflow(ins.value & 0x40);
	}
	void Core::JMP(const Instruction& ins) {
		reg_.PC = ins.address;
	}
	void Core::STY(const Instruction& ins) {
		mem_.Write(ins.address, reg_.Y);
	}
	void Core::LDY(const Instruction& ins) {
		reg_.Y = ins.value;
		SetIfZeroAndNegative(reg_.Y, reg_);
	}
	void Core::CPY(const Instruction& ins) {
		Compare(reg_.Y, ins.value);
	}
	void Core::CPX(const Instruction& ins) {
		Compare(reg_.X, ins.value);
	}
	void Core::JMP() {
		uint16_t operand = mem_.ReadWord(reg_.PC);
		// Simulate a hardware bug where crossing a page wraps instead of going through
		if ((operand & 0xFF) == 0xFF) {
			reg_.PC = mem_.Read(operand);
			reg_.PC += mem_.Read(operand & 0xFF00) << 8;
		} else {
			reg_.PC = mem_.ReadWord(operand);
		}
	}
	void Core::JSR() {
		uint16_t operand = mem_.ReadWord(reg_.PC);
		reg_.PC++;
		mem_.WriteWord(reg_.S + StackOffset - 1, reg_.PC);
		reg_.S -= 2;
		reg_.PC = operand;
	}
	void Core::BPL() {
		BranchIfClear(reg_.Negative());
	}
	void Core::BMI() {
		BranchIfSet(reg_.Negative());
	}
	void Core::BVC() {
		BranchIfClear(reg_.Overflow());
	}
	void Core::BVS() {
		BranchIfSet(reg_.Overflow());
	}
	void Core::BCC() {
		BranchIfClear(reg_.Carry());
	}
	void Core::BCS() {
		BranchIfSet(reg_.Carry());
	}
	void Core::BNE() {
		BranchIfClear(reg_.Zero());
	}
	void Core::BEQ() {
		BranchIfSet(reg_.Zero());
	}
	void Core::BRK() {
		// TODO
	}
	void Core::RTI() {
		reg_.S += 3;
		reg_.PC = mem_.ReadWord(reg_.S + StackOffset - 1);
		reg_.P = mem_.Read(reg_.S + StackOffset - 2);
	}
	void Core::RTS() {
		reg_.S += 2;
		reg_.PC = mem_.ReadWord(reg_.S + StackOffset - 1);
		reg_.PC++;
	}
	void Core::PHP() {
		mem_.Write(reg_.S + StackOffset, reg_.P);
		reg_.S--;
		reg_.SetInterrupt(1);
	}
	void Core::PLP() {
		reg_.S++;
		reg_.P = mem_.Read(reg_.S + StackOffset);
	}
	void Core::PHA() {
		mem_.Write(reg_.S + StackOffset, reg_.A);
		reg_.S--;
	}
	void Core::PLA() {
		reg_.S++;
		reg_.A = mem_.Read(reg_.S + StackOffset);
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::DEY() {
		reg_.Y--;
		SetIfZeroAndNegative(reg_.Y, reg_);
	}
	void Core::TAY() {
		reg_.Y = reg_.A;
		SetIfZeroAndNegative(reg_.Y, reg_);
	}
	void Core::INY() {
		reg_.Y++;
		SetIfZeroAndNegative(reg_.Y, reg_);
	}
	void Core::INX() {
		reg_.X++;
		SetIfZeroAndNegative(reg_.X, reg_);
	}
	void Core::CLC() {
		reg_.SetCarry(0U);
	}
	void Core::SEC() {
		reg_.SetCarry(1U);
	}
	void Core::CLI() {
		reg_.SetInterrupt(0U);
	}
	void Core::SEI() {
		reg_.SetInterrupt(1U);
	}
	void Core::TYA() {
		reg_.A = reg_.Y;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::CLV() {
		reg_.SetOverflow(0U);
	}
	void Core::CLD() {
		reg_.SetDecimal(0);
	}
	void Core::SED() {
		reg_.SetDecimal(1);
	}
	void Core::TXA() {
		reg_.A = reg_.X;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::TXS() {
		reg_.S = reg_.X;
	}
	void Core::TAX() {
		reg_.X = reg_.A;
		SetIfZeroAndNegative(reg_.X, reg_);
	}
	void Core::TSX() {
		reg_.X = reg_.S;
		SetIfZeroAndNegative(reg_.X, reg_);
	}
	void Core::DEX() {
		reg_.X--;
		SetIfZeroAndNegative(reg_.X, reg_);
	}
	void Core::NOP() {
		// No operation
	}

	// **Helper functions**
	void Core::Compare(uint8_t a, uint8_t b) {
		reg_.SetCarry(a >= b);
		reg_.SetZero(a == b);
		reg_.SetIfNegative(a - b);
	}
	uint8_t Core::Relative(uint8_t address) {
		// Returns the relative address for a signed number
		return (address & 0x80) ? ~(uint8_t)(0x100U - address) + 1U  : address;
	}
	void Core::BranchIfClear(uint8_t value) {
		// Inverting the bits will check if set
		uint8_t offset = Relative(mem_.Read(reg_.PC));
		reg_.PC += value == 0 ? offset : 0U;
		reg_.PC++;
	}
	void Core::BranchIfSet(uint8_t value) {
		uint8_t offset = Relative(mem_.Read(reg_.PC));
		reg_.PC += value == 1 ? offset : 0U;
		reg_.PC++;
	}

	// **Addressing modes**
	const Instruction Core::ZeroPageX(Instruction& ins) {
		ins.address = mem_.Read(reg_.PC) + reg_.X;
		ins.value = mem_.Read(ins.address);
		reg_.PC++;
		return ins;
	}
	const Instruction Core::ZeroPageY(Instruction& ins) {
		ins.address = mem_.Read(reg_.PC) + reg_.Y;
		ins.value = mem_.Read(ins.address);
		reg_.PC++;
		return ins;
	}
	const Instruction Core::ZeroPage(Instruction& ins) {
		ins.address = mem_.Read(reg_.PC);
		ins.value = mem_.Read(ins.address);
		reg_.PC++;
		return ins;
	}
	const Instruction Core::Immediate(Instruction& ins) {
		ins.address = reg_.PC;
		ins.value = mem_.Read(ins.address);
		reg_.PC++;
		return ins;
	}
	const Instruction Core::Absolute(Instruction& ins) {
		ins.address = mem_.ReadWord(reg_.PC);
		ins.value = mem_.Read(ins.address);
		reg_.PC += 2;
		return ins;
	}
	const Instruction Core::IndirectY(Instruction& ins) {
		ins.address = mem_.ReadWord(mem_.Read(reg_.PC) + reg_.Y);
		ins.value = mem_.Read(ins.address);
		reg_.PC++;
		return ins;
	}
	const Instruction Core::IndirectX(Instruction& ins) {
		ins.address = mem_.ReadWord((mem_.Read(reg_.PC) + reg_.X) % 0x100);
		ins.value = mem_.Read(ins.address);
		reg_.PC++;
		return ins;
	}
	const Instruction Core::AbsoluteX(Instruction& ins) {
		ins.address = mem_.ReadWord(reg_.PC) + reg_.X;
		ins.value = mem_.Read(ins.address);
		reg_.PC += 2;
		return ins;
	}
	const Instruction Core::AbsoluteY(Instruction& ins) {
		ins.address = mem_.ReadWord(reg_.PC) + reg_.Y;
		ins.value = mem_.Read(ins.address);
		reg_.PC += 2;
		return ins;
	}
	const Instruction Core::Accumulator(Instruction& ins) {
		ins.isAccumulator = true;
		return ins;
	}
}
