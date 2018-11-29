#pragma once
#include "SFML/Graphics.hpp"
#include "WindowInterface.h"

namespace wrapper {
	class SFMLWindow : public WindowInterface {
	public:
		SFMLWindow();
		const sf::RenderWindow& window();
		void ProcessEventQueue();
	private:
		sf::RenderWindow window_;
	};
}