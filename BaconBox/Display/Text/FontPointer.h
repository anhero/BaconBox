/**
 * @file
 */
#ifndef BB_FONT_POINTER_H
#define BB_FONT_POINTER_H

#include "BaconBox/ResourcePointer.h"
#include "BaconBox/ResourceManager.h"

namespace BaconBox {
	class Font;
	typedef ResourcePointer<Font, &ResourceManager::getFont> FontPointer;
}

#endif // BB_FONT_POINTER_H
