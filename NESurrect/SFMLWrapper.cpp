#include "SFMLWrapper.h"

namespace wrapper {
	SFMLWrapper::SFMLWrapper() {
		constexpr int ScreenWidth = 256;
		constexpr int ScreenHeight = 240;
		window_.create(sf::VideoMode(ScreenWidth, ScreenHeight), "NES Emulator", sf::Style::Default);
	}

	void SFMLWrapper::RenderPixels(uint8_t *const pixels) {
		frame_.update(pixels);

		window_.clear(sf::Color::Black);

		sf::Sprite frameSprite;
		frameSprite.setTexture(frame_);
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