#pragma once
#include "SFML/Graphics.hpp"
#include "WindowInterface.h"

namespace wrapper {
	class SFMLWindow : public WindowInterface {
	public:
		SFMLWindow();
		sf::RenderWindow* getWindow() { return &window_; }
		void ProcessEventQueue();
	private:
		sf::RenderWindow window_;
	};
}