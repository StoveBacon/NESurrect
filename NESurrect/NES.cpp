#include "NES.h"

NES::NES() {
	memory_ = new mem::Memory();
	core_ = new cpu::Core(memory_);
	wrapper_ = new wrapper::SFMLWrapper();
	ppu_ = new ppu::PPU(memory_, wrapper_);
}

NES::~NES() {
	delete ppu_;
	delete wrapper_;
	delete core_;
	delete memory_;
}

void NES::run() {
	while (wrapper_->isOpen()) {
		core_->executeInstruction();
		// Loose approximation, to be updated later
		for (int i = 0; i < 12; i++) {
			ppu_->runCycle();
		}
		wrapper_->ProcessEventQueue();
	}
}
