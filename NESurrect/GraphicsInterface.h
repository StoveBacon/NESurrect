#pragma once
#include <vector>
#include "WindowInterface.h"

namespace wrapper {

	// Provides an interface for rendering so that rendering systems can be swapped without affecting non-rendering code
	class GraphicsInterface {
	public:
		GraphicsInterface(WindowInterface *parent) : parentWindow_(parent) {}
		virtual ~GraphicsInterface() = default;
		virtual void DrawPixels(const std::vector<uint8_t>&) = 0;
	protected:
		WindowInterface *parentWindow_;
	};
}
