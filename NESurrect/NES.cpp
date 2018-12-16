#include "NES.h"

NES::NES() {
	cpuMem_ = new memory::CPUMemory(memoryMapper);
	core_ = new cpu::Core(cpuMem_);
	wrapper_ = new wrapper::SFMLWrapper();
}

NES::~NES() {
	delete wrapper_;
	delete core_;
	delete cpuMem_;
}

void NES::Run() {
	while (wrapper_->windowObject->IsOpen()) {
		core_->ExecuteInstruction();
		wrapper_->windowObject->ProcessEventQueue();
	}
}
