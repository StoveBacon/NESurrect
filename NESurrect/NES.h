#pragma once
#include "Core.h"
#include "WrapperTypes.h"

class NES {
public:
	NES();
	~NES();
	void Run();
private:
	cpu::Core *core_;
	mem::Memory *cpuMem_;
	wrapper::Wrapper *wrapper_;
};