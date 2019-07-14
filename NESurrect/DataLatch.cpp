#include "DataLatch.h"

namespace mem {
	void DataLatch::setValue(uint8_t value) {
		value_ = value;
		isSet_ = ~isSet_;
	}
	void DataLatch::clear() {
		isSet_ = false;
	}
	bool DataLatch::isSet() {
		return isSet_;
	}
	uint8_t DataLatch::value() {
		return value_;
	}
}