#include "SFMLWrapper.h"

namespace wrapper {
	SFMLWrapper::SFMLWrapper() {
		constexpr int ScreenWidth = 256;
		constexpr int ScreenHeight = 240;
		frame_.create(256, 240);
		window_.create(sf::VideoMode(ScreenWidth, ScreenHeight), "NES Emulator", sf::Style::Default);
		sf::Vector2u size;
		size.x = ScreenWidth * 4;
		size.y = ScreenHeight * 4;
		window_.setSize(size);
	}

	void SFMLWrapper::RenderPixels(uint8_t *const pixels) {
		
		window_.clear(sf::Color::Black);

		sf::Sprite frameSprite(frame_);
		frame_.update(pixels);
		window_.draw(frameSprite);

		window_.display();
	}

	void SFMLWrapper::ProcessEventQueue() {
		// TODO make sure window is initialized correctly
		sf::Event event;
		while (window_.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				isOpen_ = false;
				window_.close();
				return;
			}
		}
	}
}