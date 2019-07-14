#include "PPURegisters.h"

namespace mem {
	uint8_t StatusRegister::get() {
		uint8_t oldVal = value_;
		this->setBits(true, MASK_VBLANK);
		reg_->latch.clear();
		return oldVal;
	}

	void OamDataRegister::set(const uint8_t& val) {
		value_ = val;
		reg_->oamAddressReg->increment();
	}

	void DmaStartRegister::set(const uint8_t& val) {
		reg_->memory->oamDump(val);
	}

	void DoubleWriteRegister::set(const uint8_t& val) {
		if (reg_->latch.isSet()) {
			reg_->vramAddress = (reg_->latch.value() << 8);
			reg_->vramAddress += val;
		}
		reg_->latch.setValue(val);
	}

	uint8_t VramRWRegister::get() {
		uint8_t retval = reg_->memory->readVram(reg_->vramAddress);
		reg_->IncrementVramAddress();
		return retval;
	}

	void VramRWRegister::set(const uint8_t & val) {
		reg_->memory->writeVram(val, reg_->vramAddress);
		reg_->IncrementVramAddress();
	}
}