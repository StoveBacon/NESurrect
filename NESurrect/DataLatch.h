#pragma once
#include <cstdint>

namespace mem {
	class DataLatch {
	public:
		DataLatch() : value_(0), isSet_(false) {}
		void setValue(uint8_t value);
		void clear();
		bool isSet();
		uint8_t value();
	private:
		uint8_t value_;
		bool isSet_;
	};
}