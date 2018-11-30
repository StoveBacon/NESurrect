#pragma once
#include "WindowInterface.h"
#include "GraphicsInterface.h"

/* Wrapper is used to support different hardware libraries
 * by inheriting the various wrapper classes and implmenting them.
 * This is done so that wrappers can be swapped easily at runtime
 */

namespace wrapper {
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