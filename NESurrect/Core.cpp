#include "Core.h"

namespace CPU {
	void Core::ExecuteInstruction() {
		switch (mem_.Read(reg_.PC)) {
		case 0x01: ORA(IndirectX()); break;
		case 0x05: ORA(ZeroPage()); break;
		case 0x09: ORA(Immediate()); break;
		case 0x0D: ORA(Absolute()); break;
		case 0x11: ORA(IndirectY()); break;
		case 0x15: ORA(ZeroPageX()); break;
		case 0x19: ORA(AbsoluteY()); break;
		case 0x1D: ORA(AbsoluteX()); break;

		case 0x21: AND(IndirectX()); break;
		case 0x25: AND(ZeroPage()); break;
		case 0x29: AND(Immediate()); break;
		case 0x2D: AND(Absolute()); break;
		case 0x31: AND(IndirectY()); break;
		case 0x35: AND(ZeroPageX()); break;
		case 0x39: AND(AbsoluteY()); break;
		case 0x3D: AND(AbsoluteX()); break;

		case 0x41: EOR(IndirectX()); break;
		case 0x45: EOR(ZeroPage()); break;
		case 0x49: EOR(Immediate()); break;
		case 0x4D: EOR(Absolute()); break;
		case 0x51: EOR(IndirectY()); break;
		case 0x55: EOR(ZeroPageX()); break;
		case 0x59: EOR(AbsoluteY()); break;
		case 0x5D: EOR(AbsoluteX()); break;

		case 0x61: ADC(IndirectX()); break;
		case 0x65: ADC(ZeroPage()); break;
		case 0x69: ADC(Immediate()); break;
		case 0x6D: ADC(Absolute()); break;
		case 0x71: ADC(IndirectY()); break;
		case 0x75: ADC(ZeroPageX()); break;
		case 0x79: ADC(AbsoluteY()); break;
		case 0x7D: ADC(AbsoluteX()); break;

		case 0x81: STA(IndirectX()); break;
		case 0x85: STA(ZeroPage()); break;
		// case 0x89: STA(Immediate()); break; Illegal
		case 0x8D: STA(Absolute()); break;
		case 0x91: STA(IndirectY()); break;
		case 0x95: STA(ZeroPageX()); break;
		case 0x99: STA(AbsoluteY()); break;
		case 0x9D: STA(AbsoluteX()); break;

		case 0xA1: LDA(IndirectX()); break;
		case 0xA5: LDA(ZeroPage()); break;
		case 0xA9: LDA(Immediate()); break;
		case 0xAD: LDA(Absolute()); break;
		case 0xB1: LDA(IndirectY()); break;
		case 0xB5: LDA(ZeroPageX()); break;
		case 0xB9: LDA(AbsoluteY()); break;
		case 0xBD: LDA(AbsoluteX()); break;

		case 0xC1: CMP(IndirectX()); break;
		case 0xC5: CMP(ZeroPage()); break;
		case 0xC9: CMP(Immediate()); break;
		case 0xCD: CMP(Absolute()); break;
		case 0xD1: CMP(IndirectY()); break;
		case 0xD5: CMP(ZeroPageX()); break;
		case 0xD9: CMP(AbsoluteY()); break;
		case 0xDD: CMP(AbsoluteX()); break;

		case 0xE1: SBC(IndirectX()); break;
		case 0xE5: SBC(ZeroPage()); break;
		case 0xE9: SBC(Immediate()); break;
		case 0xED: SBC(Absolute()); break;
		case 0xF1: SBC(IndirectY()); break;
		case 0xF5: SBC(ZeroPageX()); break;
		case 0xF9: SBC(AbsoluteY()); break;
		case 0xFD: SBC(AbsoluteX()); break;

		// case 0x02: ASL(Immediate()); break; Illegal
		case 0x06: ASL(ZeroPage()); break;
		case 0x0A: ASL(Accumulator()); break;
		case 0x0E: ASL(Absolute()); break;
		case 0x16: ASL(ZeroPageX()); break;
		case 0x1E: ASL(AbsoluteX()); break;

		// case 0x22: ROL(Immediate()); break; Illegal
		case 0x26: ROL(ZeroPage()); break;
		case 0x2A: ROL(Accumulator()); break;
		case 0x2E: ROL(Absolute()); break;
		case 0x36: ROL(ZeroPageX()); break;
		case 0x3E: ROL(AbsoluteX()); break;

		// case 0x42: LSR(Immediate()); break; Illegal
		case 0x46: LSR(ZeroPage()); break;
		case 0x4A: LSR(Accumulator()); break;
		case 0x4E: LSR(Absolute()); break;
		case 0x56: LSR(ZeroPageX()); break;
		case 0x5E: LSR(AbsoluteX()); break;

		// case 0x62: ROR(Immediate()); break; Illegal
		case 0x66: ROR(ZeroPage()); break;
		case 0x6A: ROR(Accumulator()); break;
		case 0x6E: ROR(Absolute()); break;
		case 0x76: ROR(ZeroPageX()); break;
		case 0x7E: ROR(AbsoluteX()); break;

		// case 0x82: STX(Immediate()); break; Illegal
		case 0x86: STX(ZeroPage()); break;
		case 0x8E: STX(Absolute()); break;
		case 0x96: STX(ZeroPageY()); break;
		// case 0x9E: STX(IndirectY()); break; Illegal

		case 0xA2: LDX(Immediate()); break;
		case 0xA6: LDX(ZeroPage()); break;
		case 0xAE: LDX(Absolute()); break;
		case 0xB6: LDX(ZeroPageY()); break;
		case 0xBE: LDX(AbsoluteY()); break;

		// case 0xC2: DEC(Immediate()); break; Illegal
		case 0xC6: DEC(ZeroPage()); break;
		case 0xCE: DEC(Absolute()); break;
		case 0xD6: DEC(ZeroPageX()); break;
		case 0xDE: DEC(AbsoluteX()); break;

		// case 0xE2: INC(Immediate()); break; Illegal
		case 0xE6: INC(ZeroPage()); break;
		case 0xEE: INC(Absolute()); break;
		case 0xF6: INC(ZeroPageX()); break;
		case 0xFE: INC(AbsoluteX()); break;

		case 0x24: BIT(ZeroPage()); break;
		case 0x2C: BIT(Absolute()); break;

		case 0x4C: JMP(Absolute()); break;

		case 0x6C: JMPAbs(); break;
		case 0x20: JSRAbs(); break;
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
		}
	}

	void Core::ORA(uint8_t value) {
		reg_.A = reg_.A | value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::AND(uint8_t value) {
		reg_.A = reg_.A & value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::EOR(uint8_t value) {
		reg_.A = reg_.A ^ value;
		SetIfZeroAndNegative(reg_.A, reg_);
	}
	void Core::ADC(uint8_t value) {
		// TODO
	}
	void Core::STA(uint8_t value) {
		mem_.Write(value, reg_.A);
	}
	void Core::LDA(uint8_t value) {
		reg_.A = mem_.Read(value);
	}

	uint8_t Core::ZeroPageX() {
		uint8_t retval = mem_.Read(mem_.Read(reg_.PC) + reg_.X);
		reg_.PC++;
		return retval;
	}
	uint8_t Core::ZeroPageY() {
		uint8_t retval = mem_.Read(mem_.Read(reg_.PC) + reg_.Y);
		reg_.PC++;
		return retval;
	}
	uint8_t Core::ZeroPage() {
		uint8_t retval = mem_.Read(mem_.Read(reg_.PC));
		reg_.PC++;
		return retval;
	}
	uint8_t Core::Immediate() {
		uint8_t retval = mem_.Read(reg_.PC);
		reg_.PC++;
		return retval;
	}
	uint8_t Core::Absolute() {
		uint8_t retval = mem_.Read(mem_.ReadWord(reg_.PC));
		reg_.PC += 2;
		return retval;
	}
	uint8_t Core::IndirectY() {
		uint8_t retval = mem_.Read(mem_.ReadWord(mem_.Read(reg_.PC) + reg_.Y));
		reg_.PC++;
	}
	uint8_t Core::IndirectX() {
		uint8_t retval = mem_.Read(mem_.ReadWord((mem_.Read(reg_.PC) + reg_.X) % 0x100));
		reg_.PC++;
		return retval;
	}
	uint8_t Core::AbsoluteX() {
		uint8_t retval = mem_.Read(mem_.ReadWord(reg_.PC) + reg_.X);
		reg_.PC += 2;
		return retval;
	}
	uint8_t Core::AbsoluteY() {
		uint8_t retval = mem_.Read(mem_.ReadWord(reg_.PC) + reg_.Y);
		reg_.PC += 2;
		return retval;
	}
	uint8_t Core::Accumulator() {
		return reg_.A;
	}
}