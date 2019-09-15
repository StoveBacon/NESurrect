#include "NES.h"

NES::NES() {
	FileManager::init();
	memory = new mem::Memory();
	core = new cpu::Core(this);
	wrapper = new wrapper::SFMLWrapper();
	ppu = new ppu::PPU(memory, wrapper);
}

NES::~NES() {
	delete ppu;
	delete wrapper;
	delete core;
	delete memory;
	FileManager::close();
}

void NES::run() {
	while (wrapper->isOpen()) {
		core->executeInstruction();
		// Loose approximation, to be updated later
		for (int i = 0; i < 12; i++) {
			//ppu->runCycle();
		}
		wrapper->ProcessEventQueue();
	}
}
