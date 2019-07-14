#include "SFMLGraphics.h"

namespace wrapper {
	void SFMLGraphics::DrawPixels(const std::vector<uint8_t> &pixels) {
		const uint8_t *pixelArray = pixels.data();
		frame.update(pixelArray);

		window_->clear(sf::Color::Black);

		sf::Sprite frameSprite;
		frameSprite.setTexture(frame);
		window_->draw(frameSprite);

		window_->display();
	}
}