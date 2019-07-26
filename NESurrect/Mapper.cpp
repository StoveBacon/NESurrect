#include "Mapper.h"

void Mapper::Init(std::vector<mem::MemoryValue*> memory, std::vector<mem::MemoryValue*> vram) {
	memory_ = memory;
	vram_ = vram;
}

// NROM loader, TODO make this not bad
void Mapper::LoadCartridge(std::string filepath) {
	path_ = filepath;
	file_.open(path_, std::ios::binary);

	if (file_.is_open()) {
		// 16 bytes of header info
		for (int i = 0; i < 16; i++) {
			header_[i] = file_.get();
		}

		// if 16KB, mirror memory
		if (header_[4] == 1) {
			for (int i = 0; i <= 0x3FFF; i++) {
				uint8_t value = file_.get();
				memory_[0x8000 + i]->set(value);
				memory_[0xC000 + i]->set(value);
			}
		} else {
			for (int i = 0; i <= 0x7FFF; i++) {
				uint8_t value = file_.get();
				memory_[0x8000 + i]->set(value);
			}
		}
		for (int i = 0; i < 0x1FFF; i++) {
			vram_[i]->set(file_.get());
		}
		file_.close();
	}
}