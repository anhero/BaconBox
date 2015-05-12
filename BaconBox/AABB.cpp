#include "AABB.h"

#include <algorithm>

#include "BaconBox/Console.h"

namespace BaconBox {
	AABB::AABB() : position(), size() {
	}
	
	AABB::AABB(float x, float y, float width, float height): position(x,y), size(width, height) {
	
	}

	AABB::AABB(const VMATH_NAMESPACE::Vector2f &newPosition,
	                                               const VMATH_NAMESPACE::Vector2f &newSize) :
		position(newPosition), size(newSize) {
	}

	AABB::AABB(const AABB &src) :
		position(src.position), size(src.size) {
	}

	AABB &AABB::operator=(const AABB &src) {
		if (this != &src) {
			position = src.position;
			size = src.size;
		}

		return *this;
	}

	bool AABB::operator==(const AABB &other) const {
		return position == other.position && size == other.size;
	}

	bool AABB::operator!=(const AABB &other) const {
		return !(*this == other);
	}

	VMATH_NAMESPACE::Vector2f &AABB::getPosition() {
		return position;
	}

	const VMATH_NAMESPACE::Vector2f &AABB::getPosition() const {
		return position;
	}

	void AABB::setPosition(const VMATH_NAMESPACE::Vector2f &newPosition) {
		position = newPosition;
	}

	void AABB::setPosition(float newXPosition, float newYPosition) {
		position.x = newXPosition;
		position.y = newYPosition;
	}

	void AABB::move(const VMATH_NAMESPACE::Vector2f &delta) {
		position += delta;
	}

	void AABB::move(float xDelta, float yDelta) {
		position.x += xDelta;
		position.y += yDelta;
	}

	float AABB::getXPosition() const {
		return position.x;
	}

	void AABB::setXPosition(float newXPosition) {
		position.x = newXPosition;
	}

	void AABB::moveX(float xDelta) {
		position.x += xDelta;
	}

	float AABB::getYPosition() const {
		return position.y;
	}

	void AABB::setYPosition(float newYPosition) {
		position.y = newYPosition;
	}

	void AABB::moveY(float yDelta) {
		position.y += yDelta;
	}

	const VMATH_NAMESPACE::Vector2f AABB::getPositionCenter() const {
		return VMATH_NAMESPACE::Vector2f(position + size * 0.5f);
	}

	float AABB::getXPositionCenter() const {
		return position.x + size.x * 0.5f;
	}

	float AABB::getYPositionCenter() const {
		return position.y + size.y * 0.5f;
	}

	VMATH_NAMESPACE::Vector2f &AABB::getSize() {
		return size;
	}

	const VMATH_NAMESPACE::Vector2f &AABB::getSize() const {
		return size;
	}

	void AABB::setSize(const VMATH_NAMESPACE::Vector2f &newSize) {
		size = newSize;
	}

	void AABB::setSize(float newWidth, float newHeight) {
		size.x = newWidth;
		size.y = newHeight;
	}

	float AABB::getWidth() const {
		return size.x;
	}

	void AABB::setWidth(float newWidth) {
		size.x = newWidth;
	}

	float AABB::getHeight() const {
		return size.y;
	}

	void AABB::setHeight(float newHeight) {
		size.y = newHeight;
	}

	float AABB::getLeft() const {
		return position.x;
	}

	float AABB::getRight() const {
		return position.x + size.x;
	}

	float AABB::getTop() const {
		return position.y;
	}

	float AABB::getBottom() const {
		return position.y + size.y;
	}

	bool AABB::overlaps(const AABB &other) const {
		return getRight() > other.getLeft() && getLeft() < other.getRight() &&
		       getBottom() > other.getTop() && getTop() < other.getBottom();
	}

	bool AABB::overlaps(const VMATH_NAMESPACE::Vector2f &point) const {
		return overlaps(point.x, point.y);
	}
	
	bool AABB::overlaps(const VMATH_NAMESPACE::Vector2f &point, float radius) const{
	
		return overlaps(AABB(VMATH_NAMESPACE::Vector2f(point.x - radius, point.y - radius), VMATH_NAMESPACE::Vector2f(radius*2, radius*2)));
	}


	bool AABB::overlaps(float xPoint, float yPoint) const {
		return xPoint >= getLeft() && xPoint <= getRight() &&
		       yPoint >= getTop() && yPoint <= getBottom();
	}

	bool AABB::overlapsHorizontalLine(float yPosition,
	                                                    float lowerXBoundary,
	                                                    float higherXBoundary) const {
		// If the boundaries are reversed.
		if (lowerXBoundary > higherXBoundary) {
			// We swap them.
			float tmp = lowerXBoundary;
			lowerXBoundary = higherXBoundary;
			higherXBoundary = tmp;
		}

		return getBottom() > yPosition && getTop() < yPosition &&
		       getRight() > lowerXBoundary && getLeft() < higherXBoundary;
	}

	bool AABB::overlapsHorizontalLine(float yPosition) const {
		return getBottom() > yPosition && getTop() < yPosition;
	}

	bool AABB::overlapsVerticalLine(float xPosition,
	                                                  float lowerYBoundary,
	                                                  float higherYBoundary) const {
		// If the boundaries are reversed.
		if (lowerYBoundary > higherYBoundary) {
			// We swap them.
			float tmp = lowerYBoundary;
			lowerYBoundary = higherYBoundary;
			higherYBoundary = tmp;
		}

		return getRight() > xPosition && getLeft() < xPosition &&
		       getBottom() > lowerYBoundary && getTop() < higherYBoundary;
	}

	bool AABB::overlapsVerticalLine(float xPosition) const {
		return getRight() > xPosition && getLeft() < xPosition;
	}

	bool AABB::isCompletelyInside(const AABB &other) const {
		return this->getLeft() >= other.getLeft() &&
		       this->getRight() <= other.getRight() &&
		       this->getTop() >= other.getTop() &&
		       this->getBottom() <= other.getBottom();
	}
}
