#pragma once

namespace wrapper {
	class WindowInterface {
	public:
		virtual ~WindowInterface() = default;
		virtual void ProcessEventQueue() = 0;
		bool IsOpen() { return isOpen_; }
	protected:
		bool isOpen_;
	};
}