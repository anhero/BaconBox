#include "ColorFilter.h"

#include "BaconBox/Core/IDManager.h"

namespace BaconBox {
	BB_ID_IMPL(ColorFilter);
	
	int ColorFilter::MESSAGE_GET_COLOR = IDManager::generateID();
	int ColorFilter::MESSAGE_SET_COLOR = IDManager::generateID();

	ColorFilter::ColorFilter() : Component(), color(Color::WHITE) {
	}
	
	ColorFilter::ColorFilter(const Color &newColor) : Component(), color(newColor) {
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
		
		if (message == ColorFilter::MESSAGE_GET_COLOR) {
			*reinterpret_cast<Color *>(data) = this->getColor();
		} else if (message == ColorFilter::MESSAGE_SET_COLOR) {
			this->setColor(*reinterpret_cast<Color *>(data));
		}
	}
	
	const Color &ColorFilter::getColor() const {
		return this->color;
	}
	
	void ColorFilter::setColor(const Color &newColor) {
		this->color = newColor;
	}
}