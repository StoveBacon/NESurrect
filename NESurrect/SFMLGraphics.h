#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GraphicsInterface.h"

namespace wrapper {
	class SFMLGraphics : public GraphicsInterface {
	public:
		SFMLGraphics(WindowInterface *parent) : GraphicsInterface(parent) {}
		void Initialize(const sf::RenderWindow &window);
		void DrawPixels(const std::vector<Pixel> &pixels);
	private:
		void DrawToHardware(const std::vector<Pixel> &pixels);

		const sf::RenderWindow *window_;
	};
}
