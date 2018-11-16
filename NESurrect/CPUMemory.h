#pragma once
#include "Memory.h"

namespace CPU {
	constexpr int MemSize = 0x10000U;
	constexpr uint16_t RAMMirrorLow = 0x0000U;
	constexpr uint16_t RAMMirrorHigh = 0x2000U;
	constexpr uint16_t RAMMirrorSize = 0x0800U;
	constexpr uint16_t PPUMirrorLow = 0x2000U;
	constexpr uint16_t PPUMirrorHigh = 0x4000U;
	constexpr uint16_t PPUMirrorSize = 0x08U;

	typedef Memory<MemSize, RAMMirrorLow, RAMMirrorHigh, RAMMirrorSize, PPUMirrorLow, PPUMirrorHigh, PPUMirrorSize> CPUMemory;
}