#include "MappedRegisters.h"

namespace mem {
	MappedRegisters::MappedRegisters(MemComponent memory, MemComponent vram, MemComponent oam) {
		this->memory = memory;
		this->vram = vram;
		this->oam = oam;

		registers.push_back(new BaseRegister(this));
		registers.push_back(new BaseRegister(this));
		registers.push_back(new StatusRegister(this));
		registers.push_back(new BaseRegister(this));
		registers.push_back(new OamDataRegister(this));
		registers.push_back(new DmaStartRegister(this));
		registers.push_back(new DoubleWriteRegister(this));
		registers.push_back(new DoubleWriteRegister(this));
		registers.push_back(new VramRWRegister(this));
	}

	std::vector<MemoryValue*> MappedRegisters::GetRegisters()
	{
		return registers;
	}

	void MappedRegisters::IncrementVramAddress() {
		// This bit selects whether to move 1 or 32 each read
		uint16_t incrementMode = registers[REG_CTRL % 0x08]->getFlag(MASK_INC_MODE);
		vramAddress += (incrementMode == 0) ? 1 : 32;
	}

	uint8_t StatusRegister::get() {
		uint8_t oldVal = value_;
		this->setBits(true, MASK_VBLANK);
		reg_->latch.clear();
		return oldVal;
	}

	void OamDataRegister::set(const uint8_t& val) {
		value_ = val;
		reg_->registers[REG_OAM_ADDRESS % 0x08]->increment();
	}

	void DmaStartRegister::set(const uint8_t& val) {
		// Dumps the page that was written in
		uint16_t address = val << 8;

		// Address serves as a page offset of memory to dump into the OAM
		for (uint16_t i = 0; i < 256; i++) {
			reg_->oam[i]->set(reg_->memory[i + address]->get());
		}
	}

	void DoubleWriteRegister::set(const uint8_t& val) {
		if (reg_->latch.isSet()) {
			reg_->vramAddress = (reg_->latch.value() << 8);
			reg_->vramAddress += val;
		}
		reg_->latch.setValue(val);
	}

	uint8_t VramRWRegister::get() {
		uint8_t retval = reg_->vram[reg_->vramAddress]->get();
		reg_->IncrementVramAddress();
		return retval;
	}

	void VramRWRegister::set(const uint8_t & val) {
		reg_->vram[reg_->vramAddress]->set(val);
		reg_->IncrementVramAddress();
	}
}