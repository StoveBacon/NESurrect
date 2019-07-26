#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include "MemoryValue.h"

class Mapper {
public:
	void Init(std::vector<mem::MemoryValue*> memory, std::vector<mem::MemoryValue*> vram);
	void LoadCartridge(std::string filepath);
private:
	std::ifstream file_;
	std::string path_;
	uint8_t header_[16];
	std::vector<mem::MemoryValue*> memory_;
	std::vector<mem::MemoryValue*> vram_;
};