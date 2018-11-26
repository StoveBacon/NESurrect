#pragma once
#include "Core.h"
#include "CPUMemory.h"
#include "MemoryMapper.h"

class NES {
public:
	NES() : core(&CPUMem_) {}
	void Run();
private:
	cpu::Core core;
	memory::CPUMemory CPUMem_;
	// Memory PPUMem_;
	// Memory
};