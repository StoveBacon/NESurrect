#pragma once
#include "WrapperInterface.h"
#include "SFMLWindow.h"
#include "SFMLGraphics.h"

namespace wrapper {
	class SFMLWrapper : public WrapperInterface<SFMLWindow, SFMLGraphics> {
	public:
		void Initialize();
	};
}

