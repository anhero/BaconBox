#include "ColorFilter.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
namespace BaconBox {
	BB_ID_IMPL(ColorFilter);
	
	int ColorFilter::MESSAGE_GET_COLOR = IDManager::generatetID();
	int ColorFilter::MESSAGE_SET_COLOR = IDManager::generatetID();
	int ColorFilter::MESSAGE_COLOR_CHANGED = IDManager::generatetID();
	
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
		sendMessage(Entity::BROADCAST, MESSAGE_COLOR_CHANGED, &(this->color));

	}


	ColorFilterProxy::ColorFilterProxy(Entity *entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new ColorFilter())  {
	}
	    
		
	const Color &ColorFilterProxy::getColor() const{
	    return reinterpret_cast<ColorFilter*>(component)->getColor();
	}
	void ColorFilterProxy::setColor(const Color &newColor){
	    reinterpret_cast<ColorFilter*>(component)->setColor(newColor);
	}
}