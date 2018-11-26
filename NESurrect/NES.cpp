#include "NES.h"

void NES::Run() {
	memory::MemoryMapper mapper;
	for (;;) {
		core.ExecuteInstruction();
	}
}