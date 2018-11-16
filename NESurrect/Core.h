#pragma once
#include "CPURegisters.h"
#include "CPUMemory.h"

namespace CPU {
	class Core {
	public:
		void ExecuteInstruction();
	private:
		CPURegisters reg_;
		CPUMemory mem_;
	};
}