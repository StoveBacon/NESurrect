#pragma once
#include <cstdint>

// Wrapper provides an interface for the emulator to work with
// so that it isn't dependent on an individual library.


namespace wrapper {
	class Wrapper {
	public:
		virtual ~Wrapper() = default;
		virtual void RenderPixels(uint8_t *const pixels) = 0;
		virtual void ProcessEventQueue() = 0;
		bool isOpen() { return isOpen_;  }

	protected:
		bool isOpen_;
	};
}