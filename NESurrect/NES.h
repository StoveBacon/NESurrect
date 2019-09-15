#pragma once
#include "Core.h"
#include "PPU.h"
#include "FileManager.h"
#include "Debug.h"
#include "WrapperTypes.h"

class NES {
public:
	NES();
	~NES();
	void run();

	cpu::Core *core;
	ppu::PPU *ppu;
	mem::Memory *memory;
	wrapper::Wrapper *wrapper;
};