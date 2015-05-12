/**
 * @file
 * @ingroup Physics
 */
#ifndef BB_AXIS_ALIGNED_BOUNDING_BOX_H
#define BB_AXIS_ALIGNED_BOUNDING_BOX_H

#include "BaconBox/vmath.h"

namespace BaconBox {
	/**
	 * Represents an axis-aligned bounding box.
	 * @ingroup Physics
	 */
	class AABB {
	public:
		/**
		 * Default constructor.
		 */
		AABB();

		/**
		 * Parameterized constructor.
		 * @param newPosition Starting position.
		 * @param newSize Starting size.
		 * @see BaconBox::AABB::position
		 * @see BaconBox::AABB::size
		 */
		AABB(const VMATH_NAMESPACE::Vector2f &newPosition,
		                       const VMATH_NAMESPACE::Vector2f &newSize);
		
		AABB(float x, float y, float width, float height);

		/**
		 * Copy constructor.
		 * @param src AxisAlignedBoundingBox to make a copy of.
		 */
		AABB(const AABB &src);

		/**
		 * Assignment operator.
		 * @param src AxisAlignedBoundingBox to make a copy of.
		 * @return Reference to the modified AxisAlignedBoundingBox.
		 */
		AABB &operator=(const AABB &src);

		/**
		 * Comparison operator. Checks if both the boxes are equivalent.
		 * @param other Other box to check equality with.
		 * @return True if the boxes have the same position and size, false if
		 * not.
		 */
		bool operator==(const AABB &other) const;

		/**
		 * Comparison operator. Checks if two boxes are different.
		 * @param other Other box to check non-equality with.
		 * @return True if the boxes have different position or size, false if
		 * not.
		 */
		bool operator!=(const AABB &other) const;

		/**
		 * Gets the body's horizontal and vertical position.
		 * @return 2D vector containing the horizontal and vertical position.
		 * @see BaconBox::AABB::position
		 */
		VMATH_NAMESPACE::Vector2f &getPosition();

		/**
		 * Gets the body's horizontal and vertical position.
		 * @return 2D vector containing the horizontal and vertical position.
		 * @see BaconBox::AABB::position
		 */
		const VMATH_NAMESPACE::Vector2f &getPosition() const;

		/**
		 * Sets the AxisAlignedBoundingBox's horizontal and vertical position.
		 * @param newPosition New horizontal and vertical position.
		 * @see AABB::setPosition(float x, float y)
		 * @see BaconBox::AABB::position
		 */
		void setPosition(const VMATH_NAMESPACE::Vector2f &newPosition);

		/**
		 * Sets the AxisAlignedBoundingBox's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 * @see BaconBox::AABB::position
		 */
		void setPosition(float newXPosition, float newYPosition);

		/**
		 * Moves the AxisAlignedBoundingBox horizontally and vertically.
		 * @param delta 2D vector to add to the AxisAlignedBoundingBox's position (in
		 * pixels).
		 * @see BaconBox::AABB::move(float deltaX, float deltaY)
		 * @see BaconBox::AABB::position
		 */
		void move(const VMATH_NAMESPACE::Vector2f &delta);

		/**
		 * Moves the AxisAlignedBoundingBox horizontally and vertically.
		 * @param xDelta Value to add to the AxisAlignedBoundingBox's horizontal position
		 * (in pixels). Positive value moves the AxisAlignedBoundingBox to the right and a
		 * negative value moves the AxisAlignedBoundingBox to the left.
		 * @param yDelta Value to add to the AxisAlignedBoundingBox's vertical position (in
		 * pixels). Positive value moves the AxisAlignedBoundingBox down and a negative
		 * value moves the AxisAlignedBoundingBox up.
		 * @see BaconBox::AABB::move(const Vector2& delta);
		 * @see BaconBox::AABB::position
		 */
		void move(float xDelta, float yDelta);

		/**
		 * Gets the AxisAlignedBoundingBox's horizontal position.
		 * @return Horizontal position (in pixels). Lower value means more to
		 * the left.
		 * @see BaconBox::AABB::position
		 */
		float getXPosition() const;

		/**
		 * Sets the AxisAlignedBoundingBox's horizontal position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @see BaconBox::AABB::position
		 */
		void setXPosition(float newXPosition);

		/**
		 * Moves the body horizontally.
		 * @param xDelta Value to add to the AxisAlignedBoundingBox's horizontal position
		 * (in pixels). Positive value moves the AxisAlignedBoundingBox to the right and a
		 * negative value moves the AxisAlignedBoundingBox to the left.
		 * @see BaconBox::AABB::position
		 */
		void moveX(float xDelta);

		/**
		 * Gets the body's vertical position.
		 * @return Vertical position (in pixels). Lower value means more at the
		 * top.
		 * @see BaconBox::AABB::position
		 */
		float getYPosition() const;

		/**
		 * Sets the body's horizontal position.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 * @see BaconBox::AABB::position
		 */
		void setYPosition(float newYPosition);

		/**
		 * Moves the AxisAlignedBoundingBox vertically.
		 * @param yDelta Value to add to the AxisAlignedBoundingBox's vertical position (in
		 * pixels). Positive value moves the AxisAlignedBoundingBox down and a negative
		 * value moves the body up.
		 * @see BaconBox::AABB::position
		 */
		void moveY(float yDelta);

		/**
		 * Gets the body's center's position.
		 * @return 2D vector containing the body's center's position.
		 */
		const VMATH_NAMESPACE::Vector2f getPositionCenter() const;

		/**
		 * Gets the body's center's horizontal position.
		 * @return Body's center's horizontal position.
		 */
		float getXPositionCenter() const;

		/**
		 * Gets the body's center's vertical position.
		 * @return Body's center vertical position.
		 */
		float getYPositionCenter() const;

		/**
		 * Gets the bounding box's size.
		 * @return Vector2 containing the width and height of the bounding box.
		 * @see BaconBox::AABB::size
		 */
		VMATH_NAMESPACE::Vector2f &getSize();

		/**
		 * Gets the bounding box's size.
		 * @return Vector2 containing the width and height of the bounding box.
		 * @see BaconBox::AABB::size
		 */
		const VMATH_NAMESPACE::Vector2f &getSize() const;

		/**
		 * Sets the bounding box's size.
		 * @param newSize New size to set.
		 * @see BaconBox::AABB::size
		 */
		void setSize(const VMATH_NAMESPACE::Vector2f &newSize);

		/**
		 * Sets the bounding box's size.
		 * @param newWidth New width to set.
		 * @param newHeight New height to set.
		 * @see BaconBox::AABB::size
		 */
		void setSize(float newWidth, float newHeight);

		/**
		 * Gets the bounding box's width.
		 * @return Width in pixels (by default).
		 * @see BaconBox::AABB::size
		 */
		float getWidth() const;

		/**
		 * Sets the bounding box's width.
		 * @param newWidth New width to set.
		 * @see BaconBox::AABB::size
		 */
		void setWidth(float newWidth);

		/**
		 * Gets the bounding box's height.
		 * @return Height in pixels (by default).
		 * @see BaconBox::AABB::size
		 */
		float getHeight() const;

		/**
		 * Sets the bounding box's height.
		 * @param newHeight New height to set.
		 * @see BaconBox::AABB::size
		 */
		void setHeight(float newHeight);

		/**
		 * Gets the bounding box's left side's horizontal coordinate.
		 * @return Left side's horizontal position.
		 */
		float getLeft() const;

		/**
		 * Gets the bounding box's right side's horizontal coordinate.
		 * @return Right side's horizontal coordinate.
		 */
		float getRight() const;

		/**
		 * Gets the bounding box's top side's vertical coordinate.
		 * @return Top side's vertical coordinate.
		 */
		float getTop() const;

		/**
		 * Gets the bounding box's bottom side's vertical coordinate.
		 * @return Bottom side's vertical coordinate.
		 */
		float getBottom() const;

		/**
		 * Checks if the bounding box overlaps with another bounding box.
		 * @param other Bounding box to check overlapping with.
		 * @return True if the two bounding boxes collide, false if not.
		 */
		bool overlaps(const AABB &other) const;

		/**
		 * Checks if a point overlaps with the bounding box.
		 * @param point Point to check overlapping with.
		 * @return True if the point is inside the bounding box, false if not.
		 */
		bool overlaps(const VMATH_NAMESPACE::Vector2f &point) const;
		
		bool overlaps(const VMATH_NAMESPACE::Vector2f &point, float radius) const;


		/**
		 * Checks if a point overlaps with the bounding box.
		 * @param xPoint Horizontal coordinate of the point to check overlapping
		 * with.
		 * @param yPoint Vertical coordinate of the point to check overlapping
		 * with.
		 * @return True if the point is inside the bounding box, false if not.
		 */
		bool overlaps(float xPoint, float yPoint) const;

		/**
		 * Checks if the bounding box overlaps with a horizontal line. If the
		 * lower boundary given is higher than the other boundary, they will
		 * be swapped.
		 * @param yPosition Vertical position of the horizontal line to check
		 * overlapping with.
		 * @param lowerXBoundary Lower horizontal boundary of the line.
		 * @param higherXBoundary Higher horizontal boundary of the line.
		 * @return True if the bounding box overlaps with the horizontal line,
		 * false if not.
		 */
		bool overlapsHorizontalLine(float yPosition,
		                            float lowerXBoundary,
		                            float higherXBoundary) const;

		/**
		 * Checks if the bounding box overlaps with a horizontal line.
		 * @param yPosition Vertical position of the horizontal line to check
		 * overlapping with.
		 * @return True if the bounding box overlaps with the horizontal line,
		 * false if not.
		 */
		bool overlapsHorizontalLine(float yPosition) const;

		/**
		 * Checks if the bounding box overlaps with a vertical line. If the
		 * lower boundary given is higher than the other boundary, they will
		 * be swapped.
		 * @param xPosition Horizontal position of the vertical line to check
		 * overlapping with.
		 * @param lowerYBoundary Lower vertical boundary of the line.
		 * @param higherYBoundary Higher vertical boundary of the line.
		 * @return True if the bounding box overlaps with the vertical line,
		 * false if not.
		 */
		bool overlapsVerticalLine(float xPosition, float lowerYBoundary,
		                          float higherYBoundary) const;

		/**
		 * Checks if the bounding box overlaps with a vertical line.
		 * @param xPosition Horizontal position of the vertical line to check
		 * overlapping with.
		 * @return True if the bounding box overlaps with the vertical line,
		 * false if not.
		 */
		bool overlapsVerticalLine(float xPosition) const;

		/**
		 * Checks whether or not the current box is completely inside another
		 * box.
		 * @param other Box to check if it completely envelops the instance.
		 * @return True if the instance is completely inside the given box,
		 * false if not.
		 */
		bool isCompletelyInside(const AABB &other) const;
	private:
		/**
		 * Horizontal and vertical position. Position (0, 0) is at the upper
		 * left corner. The higher the horizontal value, the more to the right
		 * the body is. The higher the vertical value, the more to the bottom
		 * the body is.
		 */
		VMATH_NAMESPACE::Vector2f position;

		/// Size in pixels (by default) of the bounding box.
		VMATH_NAMESPACE::Vector2f size;
	};

}

#endif
