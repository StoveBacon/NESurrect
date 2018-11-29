#pragma once
#include "Core.h"
#include "CPUMemory.h"
#include "WrapperTypes.h"
#include "MemoryMapper.h"

class NES {
public:
	NES();
	~NES();
	void Run();
private:
	cpu::Core *core_;
	memory::CPUMemory *cpuMem_;
	wrapper::Wrapper *wrapper_;
};