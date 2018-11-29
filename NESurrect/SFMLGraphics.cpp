#include "SFMLGraphics.h"

namespace wrapper {
	void SFMLGraphics::Initialize(const sf::RenderWindow& window) {
		window_ = &window;
	}

	void SFMLGraphics::DrawPixels(const std::vector<Pixel>& pixels) {
		
	}

	void SFMLGraphics::DrawToHardware(const std::vector<Pixel>&) {

	}
}