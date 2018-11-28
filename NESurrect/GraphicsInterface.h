#pragma once
#include <vector>

namespace system {
	// Forward declaration so that this system doesn't have to know about the implementation of the picture processor
	class Pixel;

	// Provides an interface for rendering so that rendering systems can be swapped without affecting non-rendering code
	class GraphicsInterface {
	public:
		virtual ~GraphicsInterface() = default;
		virtual void Initialize() = 0;
		virtual void DrawPixels(const std::vector<Pixel>&) = 0;
	protected:
		virtual void DrawToHardware(const std::vector<Pixel>&) = 0;
	};
}
