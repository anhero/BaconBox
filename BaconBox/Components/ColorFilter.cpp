#include "ColorFilter.h"

namespace BaconBox {
	BB_ID_IMPL(ColorFilter);

	ColorFilter::ColorFilter() : Component(), color(Color::BLACK) {
	}

	ColorFilter::ColorFilter(const ColorFilter &src) : Component(src), color(src.color) {
	}

	ColorFilter::~ColorFilter() {
	}

	ColorFilter &ColorFilter::operator=(const ColorFilter &src) {
		if (this != &src) {
			this->color = src.color;
		}

		return *this;
	}

	ColorFilter *ColorFilter::clone() const {
		return new ColorFilter(*this);
	}

	void ColorFilter::receiveMessage(int senderID, int destID, int message, void *data) {
		if (destID != ColorFilter::ID) {
			return;
		}

		switch (message) {
		case ColorFilter::MESSAGE_GET_COLOR:
			*reinterpret_cast<Color *>(data) = this->getColor();
			break;

		case ColorFilter::MESSAGE_SET_COLOR:
			this->setColor(*reinterpret_cast<Color *>(data));
			break;

		default:
			break;
		}
	}
}