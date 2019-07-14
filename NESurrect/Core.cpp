#include "Core.h"

namespace cpu {
	Core::Core(mem::Memory* mem) {
		this->mem_ = mem;
		reset();
	}
	void Core::reset() {
		constexpr uint16_t ResetVector = 0xFFFC;
		constexpr uint8_t StatusDefault = 0x24;
		constexpr uint8_t SPDefault = 0xFD;
		reg.PC = mem_->readWord(ResetVector);
		reg.P = StatusDefault;
		reg.S = SPDefault;
	}
	void Core::executeInstruction() {
		Instruction ins;
		ins.opcode = mem_->readByte(reg.PC);
		reg.PC++;

		// Read the opcode. If it is an addressed mode,  pass the correct addressing function to the instruction,
		// which contains data about the memory operation.
		// Otherwise, it's a single byte instruction that just executes straight away.
		switch (ins.opcode) {
		case 0x01: ORA(indirectX(ins)); break;
		case 0x05: ORA(zeroPage(ins)); break;
		case 0x09: ORA(immediate(ins)); break;
		case 0x0D: ORA(absolute(ins)); break;
		case 0x11: ORA(indirectY(ins)); break;
		case 0x15: ORA(zeroPageX(ins)); break;
		case 0x19: ORA(absoluteY(ins)); break;
		case 0x1D: ORA(absoluteX(ins)); break;

		case 0x21: AND(indirectX(ins)); break;
		case 0x25: AND(zeroPage(ins)); break;
		case 0x29: AND(immediate(ins)); break;
		case 0x2D: AND(absolute(ins)); break;
		case 0x31: AND(indirectY(ins)); break;
		case 0x35: AND(zeroPageX(ins)); break;
		case 0x39: AND(absoluteY(ins)); break;
		case 0x3D: AND(absoluteX(ins)); break;

		case 0x41: EOR(indirectX(ins)); break;
		case 0x45: EOR(zeroPage(ins)); break;
		case 0x49: EOR(immediate(ins)); break;
		case 0x4D: EOR(absolute(ins)); break;
		case 0x51: EOR(indirectY(ins)); break;
		case 0x55: EOR(zeroPageX(ins)); break;
		case 0x59: EOR(absoluteY(ins)); break;
		case 0x5D: EOR(absoluteX(ins)); break;

		case 0x61: ADC(indirectX(ins)); break;
		case 0x65: ADC(zeroPage(ins)); break;
		case 0x69: ADC(immediate(ins)); break;
		case 0x6D: ADC(absolute(ins)); break;
		case 0x71: ADC(indirectY(ins)); break;
		case 0x75: ADC(zeroPageX(ins)); break;
		case 0x79: ADC(absoluteY(ins)); break;
		case 0x7D: ADC(absoluteX(ins)); break;

		case 0x81: STA(indirectX(ins)); break;
		case 0x85: STA(zeroPage(ins)); break;
		// case 0x89: STA(immediate(ins)); break; Illegal
		case 0x8D: STA(absolute(ins)); break;
		case 0x91: STA(indirectY(ins)); break;
		case 0x95: STA(zeroPageX(ins)); break;
		case 0x99: STA(absoluteY(ins)); break;
		case 0x9D: STA(absoluteX(ins)); break;

		case 0xA1: LDA(indirectX(ins)); break;
		case 0xA5: LDA(zeroPage(ins)); break;
		case 0xA9: LDA(immediate(ins)); break;
		case 0xAD: LDA(absolute(ins)); break;
		case 0xB1: LDA(indirectY(ins)); break;
		case 0xB5: LDA(zeroPageX(ins)); break;
		case 0xB9: LDA(absoluteY(ins)); break;
		case 0xBD: LDA(absoluteX(ins)); break;

		case 0xC1: CMP(indirectX(ins)); break;
		case 0xC5: CMP(zeroPage(ins)); break;
		case 0xC9: CMP(immediate(ins)); break;
		case 0xCD: CMP(absolute(ins)); break;
		case 0xD1: CMP(indirectY(ins)); break;
		case 0xD5: CMP(zeroPageX(ins)); break;
		case 0xD9: CMP(absoluteY(ins)); break;
		case 0xDD: CMP(absoluteX(ins)); break;

		case 0xE1: SBC(indirectX(ins)); break;
		case 0xE5: SBC(zeroPage(ins)); break;
		case 0xE9: SBC(immediate(ins)); break;
		case 0xED: SBC(absolute(ins)); break;
		case 0xF1: SBC(indirectY(ins)); break;
		case 0xF5: SBC(zeroPageX(ins)); break;
		case 0xF9: SBC(absoluteY(ins)); break;
		case 0xFD: SBC(absoluteX(ins)); break;

		// case 0x02: ASL(immediate(ins)); break; Illegal
		case 0x06: ASL(zeroPage(ins)); break;
		case 0x0A: ASL(accumulator(ins)); break;
		case 0x0E: ASL(absolute(ins)); break;
		case 0x16: ASL(zeroPageX(ins)); break;
		case 0x1E: ASL(absoluteX(ins)); break;

		// case 0x22: ROL(immediate(ins)); break; Illegal
		case 0x26: ROL(zeroPage(ins)); break;
		case 0x2A: ROL(accumulator(ins)); break;
		case 0x2E: ROL(absolute(ins)); break;
		case 0x36: ROL(zeroPageX(ins)); break;
		case 0x3E: ROL(absoluteX(ins)); break;

		// case 0x42: LSR(immediate(ins)); break; Illegal
		case 0x46: LSR(zeroPage(ins)); break;
		case 0x4A: LSR(accumulator(ins)); break;
		case 0x4E: LSR(absolute(ins)); break;
		case 0x56: LSR(zeroPageX(ins)); break;
		case 0x5E: LSR(absoluteX(ins)); break;

		// case 0x62: ROR(immediate(ins)); break; Illegal
		case 0x66: ROR(zeroPage(ins)); break;
		case 0x6A: ROR(accumulator(ins)); break;
		case 0x6E: ROR(absolute(ins)); break;
		case 0x76: ROR(zeroPageX(ins)); break;
		case 0x7E: ROR(absoluteX(ins)); break;

		// case 0x82: STX(immediate(ins)); break; Illegal
		case 0x86: STX(zeroPage(ins)); break;
		case 0x8E: STX(absolute(ins)); break;
		case 0x96: STX(zeroPageY(ins)); break;
		// case 0x9E: STX(indirectY(ins)); break; Illegal

		case 0xA2: LDX(immediate(ins)); break;
		case 0xA6: LDX(zeroPage(ins)); break;
		case 0xAE: LDX(absolute(ins)); break;
		case 0xB6: LDX(zeroPageY(ins)); break;
		case 0xBE: LDX(absoluteY(ins)); break;

		// case 0xC2: DEC(immediate(ins)); break; Illegal
		case 0xC6: DEC(zeroPage(ins)); break;
		case 0xCE: DEC(absolute(ins)); break;
		case 0xD6: DEC(zeroPageX(ins)); break;
		case 0xDE: DEC(absoluteX(ins)); break;

		// case 0xE2: INC(immediate(ins)); break; Illegal
		case 0xE6: INC(zeroPage(ins)); break;
		case 0xEE: INC(absolute(ins)); break;
		case 0xF6: INC(zeroPageX(ins)); break;
		case 0xFE: INC(absoluteX(ins)); break;

		case 0x24: BIT(zeroPage(ins)); break;
		case 0x2C: BIT(absolute(ins)); break;

		case 0x4C: JMP(absolute(ins)); break;

		case 0x84: STY(zeroPage(ins)); break;
		case 0x8C: STY(absolute(ins)); break;
		case 0x94: STY(zeroPageX(ins)); break;

		case 0xA0: LDY(immediate(ins)); break;
		case 0xA4: LDY(zeroPage(ins)); break;
		case 0xAC: LDY(absolute(ins)); break;
		case 0xB4: LDY(zeroPageX(ins)); break;
		case 0xBC: LDY(absoluteX(ins)); break;

		case 0xC0: CPY(immediate(ins)); break;
		case 0xC4: CPY(zeroPage(ins)); break;
		case 0xCC: CPY(absolute(ins)); break;

		case 0xE0: CPX(immediate(ins)); break;
		case 0xE4: CPX(zeroPage(ins)); break;
		case 0xEC: CPX(absolute(ins)); break;

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
		reg.A = reg.A | ins.value;
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::AND(const Instruction& ins) {
		reg.A = reg.A & ins.value;
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::EOR(const Instruction& ins) {
		reg.A = reg.A ^ ins.value;
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::ADC(const Instruction& ins) {
		uint8_t result = reg.A + ins.value + reg.carry();
		setIfZeroAndNegative(result, reg);
		reg.setOverflow(((ins.value & 0x80) == (reg.A & 0x80)) && ((result & 0x80) != (reg.A & 0x80)));
		reg.setCarry(result < reg.A);
		reg.A = result;
	}
	void Core::STA(const Instruction& ins) {
		mem_->writeByte(ins.address, reg.A);
	}
	void Core::LDA(const Instruction& ins) {
		reg.A = ins.value;
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::CMP(const Instruction& ins) {
		compare(reg.A, ins.value);
	}
	void Core::SBC(const Instruction& ins) {
		Instruction temp = ins;
		temp.value ^= 0xFF;
		ADC(temp);
	}
	void Core::ASL(const Instruction& ins) {
		if (ins.isAccumulator) {
			reg.setCarry(reg.A & 0x80);
			reg.A = reg.A << 1;
			setIfZeroAndNegative(reg.A, reg);
		} else {
			uint8_t shifted = ins.value << 1;
			reg.setCarry(ins.value & 0x80);
			mem_->writeByte(ins.address, shifted);
			setIfZeroAndNegative(shifted, reg);
		}
	}
	void Core::ROL(const Instruction& ins) {
		if (ins.isAccumulator) {
			uint8_t shifted = (reg.A << 1) | reg.carry();
			reg.setCarry(reg.A & 0x80);
			reg.A = shifted;
			setIfZeroAndNegative(shifted, reg);
		} else {
			uint8_t shifted = (ins.value << 1) | reg.carry();
			reg.setCarry(ins.value & 0x80);
			mem_->writeByte(ins.address, shifted);
			setIfZeroAndNegative(shifted, reg);
		}
	}
	void Core::LSR(const Instruction& ins) {
		if (ins.isAccumulator) {
			reg.setCarry(reg.A & 0x01);
			reg.A = reg.A >> 1;
			setIfZeroAndNegative(reg.A, reg);
		} else {
			uint8_t shifted = ins.value >> 1;
			reg.setCarry(ins.value & 0x01);
			mem_->writeByte(ins.address, shifted);
			setIfZeroAndNegative(shifted, reg);
		}
	}
	void Core::ROR(const Instruction& ins) {
		if (ins.isAccumulator) {
			uint8_t shifted = (reg.A >> 1) | (reg.carry() << 7);
			reg.setCarry(reg.A & 0x01);
			reg.A = shifted;
			setIfZeroAndNegative(reg.A, reg);
		} else {
			uint8_t shifted = (ins.value >> 1) | (reg.carry() << 7);
			reg.setCarry(ins.value & 0x01);
			mem_->writeByte(ins.address, shifted);
			setIfZeroAndNegative(shifted, reg);
		}
	}
	void Core::STX(const Instruction& ins) {
		mem_->writeByte(ins.address, reg.X);
	}
	void Core::LDX(const Instruction& ins) {
		reg.X = ins.value;
		setIfZeroAndNegative(reg.X, reg);
	}
	void Core::DEC(const Instruction& ins) {
		mem_->writeByte(ins.address, ins.value - 1);
		setIfZeroAndNegative(ins.value - 1, reg);
	}
	void Core::INC(const Instruction& ins) {
		mem_->writeByte(ins.address, ins.value + 1);
		setIfZeroAndNegative(ins.value + 1, reg);
	}
	void Core::BIT(const Instruction& ins) {
		reg.setIfZero(reg.A & ins.value);
		reg.setIfNegative(ins.value);
		reg.setOverflow(ins.value & 0x40);
	}
	void Core::JMP(const Instruction& ins) {
		reg.PC = ins.address;
	}
	void Core::STY(const Instruction& ins) {
		mem_->writeByte(ins.address, reg.Y);
	}
	void Core::LDY(const Instruction& ins) {
		reg.Y = ins.value;
		setIfZeroAndNegative(reg.Y, reg);
	}
	void Core::CPY(const Instruction& ins) {
		compare(reg.Y, ins.value);
	}
	void Core::CPX(const Instruction& ins) {
		compare(reg.X, ins.value);
	}
	void Core::JMP() {
		uint16_t operand = mem_->readWord(reg.PC);
		// Simulate a hardware bug where crossing a page wraps instead of going through
		if ((operand & 0xFF) == 0xFF) {
			reg.PC = mem_->readByte(operand);
			reg.PC += mem_->readByte(operand & 0xFF00) << 8;
		} else {
			reg.PC = mem_->readWord(operand);
		}
	}
	void Core::JSR() {
		uint16_t operand = mem_->readWord(reg.PC);
		reg.PC++;
		mem_->writeWord(reg.S + StackOffset - 1, reg.PC);
		reg.S -= 2;
		reg.PC = operand;
	}
	void Core::BPL() {
		branchIfClear(reg.negative());
	}
	void Core::BMI() {
		branchIfSet(reg.negative());
	}
	void Core::BVC() {
		branchIfClear(reg.overflow());
	}
	void Core::BVS() {
		branchIfSet(reg.overflow());
	}
	void Core::BCC() {
		branchIfClear(reg.carry());
	}
	void Core::BCS() {
		branchIfSet(reg.carry());
	}
	void Core::BNE() {
		branchIfClear(reg.zero());
	}
	void Core::BEQ() {
		branchIfSet(reg.zero());
	}
	void Core::BRK() {
		// TODO
	}
	void Core::RTI() {
		reg.S += 3;
		reg.PC = mem_->readWord(reg.S + StackOffset - 1);
		reg.P = mem_->readByte(reg.S + StackOffset - 2);
	}
	void Core::RTS() {
		reg.S += 2;
		reg.PC = mem_->readWord(reg.S + StackOffset - 1);
		reg.PC++;
	}
	void Core::PHP() {
		mem_->writeByte(reg.S + StackOffset, reg.P);
		reg.S--;
		reg.setInterrupt(1);
	}
	void Core::PLP() {
		reg.S++;
		reg.P = mem_->readByte(reg.S + StackOffset);
	}
	void Core::PHA() {
		mem_->writeByte(reg.S + StackOffset, reg.A);
		reg.S--;
	}
	void Core::PLA() {
		reg.S++;
		reg.A = mem_->readByte(reg.S + StackOffset);
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::DEY() {
		reg.Y--;
		setIfZeroAndNegative(reg.Y, reg);
	}
	void Core::TAY() {
		reg.Y = reg.A;
		setIfZeroAndNegative(reg.Y, reg);
	}
	void Core::INY() {
		reg.Y++;
		setIfZeroAndNegative(reg.Y, reg);
	}
	void Core::INX() {
		reg.X++;
		setIfZeroAndNegative(reg.X, reg);
	}
	void Core::CLC() {
		reg.setCarry(0U);
	}
	void Core::SEC() {
		reg.setCarry(1U);
	}
	void Core::CLI() {
		reg.setInterrupt(0U);
	}
	void Core::SEI() {
		reg.setInterrupt(1U);
	}
	void Core::TYA() {
		reg.A = reg.Y;
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::CLV() {
		reg.setOverflow(0U);
	}
	void Core::CLD() {
		reg.setDecimal(0);
	}
	void Core::SED() {
		reg.setDecimal(1);
	}
	void Core::TXA() {
		reg.A = reg.X;
		setIfZeroAndNegative(reg.A, reg);
	}
	void Core::TXS() {
		reg.S = reg.X;
	}
	void Core::TAX() {
		reg.X = reg.A;
		setIfZeroAndNegative(reg.X, reg);
	}
	void Core::TSX() {
		reg.X = reg.S;
		setIfZeroAndNegative(reg.X, reg);
	}
	void Core::DEX() {
		reg.X--;
		setIfZeroAndNegative(reg.X, reg);
	}
	void Core::NOP() {
		// No operation
	}

	// **Helper functions**
	void Core::compare(uint8_t a, uint8_t b) {
		reg.setCarry(a >= b);
		reg.setZero(a == b);
		reg.setIfNegative(a - b);
	}
	uint8_t Core::relative(uint8_t address) {
		// Returns the relative address for a signed number
		return (address & 0x80) ? ~(uint8_t)(0x100U - address) + 1U  : address;
	}
	void Core::branchIfClear(uint8_t value) {
		uint8_t offset = relative(mem_->readByte(reg.PC));
		reg.PC += value == 0 ? offset : 0U;
		reg.PC++;
	}
	void Core::branchIfSet(uint8_t value) {
		uint8_t offset = relative(mem_->readByte(reg.PC));
		reg.PC += value == 1 ? offset : 0U;
		reg.PC++;
	}

	// **Addressing modes**
	const Instruction Core::zeroPageX(Instruction& ins) {
		ins.address = mem_->readByte(reg.PC) + reg.X;
		ins.value = mem_->readByte(ins.address);
		reg.PC++;
		return ins;
	}
	const Instruction Core::zeroPageY(Instruction& ins) {
		ins.address = mem_->readByte(reg.PC) + reg.Y;
		ins.value = mem_->readByte(ins.address);
		reg.PC++;
		return ins;
	}
	const Instruction Core::zeroPage(Instruction& ins) {
		ins.address = mem_->readByte(reg.PC);
		ins.value = mem_->readByte(ins.address);
		reg.PC++;
		return ins;
	}
	const Instruction Core::immediate(Instruction& ins) {
		ins.address = reg.PC;
		ins.value = mem_->readByte(ins.address);
		reg.PC++;
		return ins;
	}
	const Instruction Core::absolute(Instruction& ins) {
		ins.address = mem_->readWord(reg.PC);
		ins.value = mem_->readByte(ins.address);
		reg.PC += 2;
		return ins;
	}
	const Instruction Core::indirectY(Instruction& ins) {
		ins.address = mem_->readWord(mem_->readByte(reg.PC) + reg.Y);
		ins.value = mem_->readByte(ins.address);
		reg.PC++;
		return ins;
	}
	const Instruction Core::indirectX(Instruction& ins) {
		ins.address = mem_->readWord((mem_->readByte(reg.PC) + reg.X) % 0x100);
		ins.value = mem_->readByte(ins.address);
		reg.PC++;
		return ins;
	}
	const Instruction Core::absoluteX(Instruction& ins) {
		ins.address = mem_->readWord(reg.PC) + reg.X;
		ins.value = mem_->readByte(ins.address);
		reg.PC += 2;
		return ins;
	}
	const Instruction Core::absoluteY(Instruction& ins) {
		ins.address = mem_->readWord(reg.PC) + reg.Y;
		ins.value = mem_->readByte(ins.address);
		reg.PC += 2;
		return ins;
	}
	const Instruction Core::accumulator(Instruction& ins) {
		ins.isAccumulator = true;
		return ins;
	}
}
