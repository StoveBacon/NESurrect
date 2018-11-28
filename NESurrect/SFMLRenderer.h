#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GraphicsInterface.h"

namespace system {
	class SFMLRenderer : public GraphicsInterface {
		void DrawPixels(const std::vector<Pixel>&);
	private:
		void DrawToHardware(const std::vector<Pixel>&);
	};
}
