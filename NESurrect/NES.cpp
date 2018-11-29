#include "NES.h"

void NES::Run() {
	wrapper::SFMLWrapper wrapper;
	wrapper.Initialize();

	while (wrapper.windowObject.IsOpen()) {
		core.ExecuteInstruction();
	}
}