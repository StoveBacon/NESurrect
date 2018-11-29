#pragma once
#include "SFML/Graphics.hpp"

namespace wrapper {
	class WindowInterface {
	public:
		~WindowInterface() = default;
		virtual void ProcessEventQueue() = 0;
		bool IsOpen() { return isOpen_; }
	protected:
		bool isOpen_;
	};
}