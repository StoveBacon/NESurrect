#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GraphicsInterface.h"

namespace wrapper {
	class SFMLGraphics : public GraphicsInterface {
	public:
		void Initialize(const sf::RenderWindow &window);
		void DrawPixels(const std::vector<Pixel>&);
	private:
		void DrawToHardware(const std::vector<Pixel>&);

		const sf::RenderWindow *window_;
	};
}
