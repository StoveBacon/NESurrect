#pragma once
#include "Core.h"
#include "CPUMemory.h"
#include "WrapperTypes.h"

class NES {
public:
	NES();
	~NES();
	void Run();
private:
	cpu::Core *core_;
	wrapper::Wrapper *wrapper_;
};