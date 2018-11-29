#pragma once
#include "Wrapper.h"
#include "SFMLWindow.h"
#include "SFMLGraphics.h"

namespace wrapper {
	typedef WrapperType<SFMLWindow, SFMLGraphics> SFMLWrapper;
}