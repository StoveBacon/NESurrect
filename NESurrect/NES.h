#pragma once
#include "Core.h"
#include "PPU.h"
#include "WrapperTypes.h"

class NES {
public:
	NES();
	~NES();
	void run();
private:
	cpu::Core *core_;
	ppu::PPU *ppu_;
	mem::Memory *memory_;
	wrapper::Wrapper *wrapper_;
};