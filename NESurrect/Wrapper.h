#pragma once
#include "WindowInterface.h"
#include "GraphicsInterface.h"

namespace wrapper {
	// The wrapper exists for polymorphic purposes
	// while WrapperType is used to assign specific wrappers
	class Wrapper {
	public:
		virtual ~Wrapper() = default;
		WindowInterface *windowObject;
		GraphicsInterface *graphicsObject;
	};

	template<class WindowClass, class GraphicsClass>
	class WrapperType : public Wrapper {
	public:
		WrapperType() {
			windowObject = new WindowClass;
			graphicsObject = new GraphicsClass(windowObject);
		}
		~WrapperType() {
			delete graphicsObject;
			delete windowObject;
		}
	};
}