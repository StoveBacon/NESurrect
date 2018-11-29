#pragma once

// Provides an interface for creating different types of wrappers.
// Forces initialization so that error checking can be done on the components

namespace wrapper {
	template<class Window, class Graphics>
	class WrapperInterface {
	public:
		virtual void Initialize() = 0;

		Window windowObject;
		Graphics graphicsObject;
	};
}