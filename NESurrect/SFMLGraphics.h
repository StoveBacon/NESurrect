#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GraphicsInterface.h"
#include "SFMLWindow.h"

namespace wrapper {
	class SFMLGraphics : public GraphicsInterface {
	public:
		SFMLGraphics(WindowInterface *parent) : GraphicsInterface(parent) { if (!frame.create(256, 240)) { /* TODO: Log error */ }}
		void DrawPixels(const std::vector<uint8_t> &pixels);
	private:

		sf::RenderWindow *window_;
		sf::Texture frame;
	};
}
