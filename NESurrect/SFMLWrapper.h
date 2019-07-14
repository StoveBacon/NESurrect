#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Wrapper.h"

namespace wrapper {
	class SFMLWrapper : public Wrapper {
	public:
		SFMLWrapper();
		void RenderPixels(uint8_t * const pixels);
		void ProcessEventQueue();

	private:
		sf::RenderWindow window_;
		sf::Texture frame_;
	};
}