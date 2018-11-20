#include "Core.h"

int main() {
	CPU::Core core;
	for (;;) {
		core.ExecuteInstruction();
	}
	
	return 0;
}