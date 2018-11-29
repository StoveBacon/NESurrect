#include "SFMLWindow.h"

namespace wrapper {
	SFMLWindow::SFMLWindow() {
		constexpr int ScreenWidth = 256;
		constexpr int ScreenHeight = 240;
		window_.create(sf::VideoMode(ScreenWidth, ScreenHeight), "NES Emulator", sf::Style::Default);
	}

	const sf::RenderWindow& SFMLWindow::window() {
		return window_;
	}

	void SFMLWindow::ProcessEventQueue() {
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

