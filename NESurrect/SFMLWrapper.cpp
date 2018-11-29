#include "SFMLWrapper.h"

namespace wrapper {
	void SFMLWrapper::Initialize() {
		// TODO: Error check here
		graphicsObject.Initialize(windowObject.window());
	}
}