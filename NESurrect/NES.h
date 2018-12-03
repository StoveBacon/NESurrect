#pragma once
#include "Core.h"
#include "CPUMemory.h"
#include "MemoryMapper.h"
#include "WrapperTypes.h"

class NES {
public:
	NES();
	~NES();
	void Run();
private:
	cpu::Core *core_;
	memory::CPUMemory *cpuMem_;
	memory::MemoryMapper *memoryMapper;
	wrapper::Wrapper *wrapper_;
};