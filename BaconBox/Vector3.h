/**
 * @file
 * @ingroup Math
 */
#ifndef BB_VECTOR3_H
#define BB_VECTOR3_H

#include "BaconBox/Vector2.h"

namespace BaconBox {
	template <typename T>
	class Vector<T, 3u> {
	public:
		/// Fundamental floating point number type the vector contains.
		typedef T ValueType;
		/// Number of dimensions the vector has.
		static const unsigned int NB_DIMENSIONS = 3u;
		/// Typedef for easier reading and writing.
		typedef Vector<ValueType, NB_DIMENSIONS> Vector3;
		/// Normalized vector that points up.
		static const Vector<ValueType, NB_DIMENSIONS> UP;
		/// Value equal to zero.
		static const ValueType ZERO;
		
		/// Type of component, either on the X axis or Y axis.
		enum ComponentType {
		    X,
		    Y,
			Z
		};
		
		/**
		 * Represents a component of a Vector3.
		 * @tparam C Either X or Y.
		 */
		template <ComponentType C>
		struct Component {
			Component() : value(ZERO) {}
			Component(ValueType newValue) : value(newValue) {}
			Component(const Component<C> &src) : value(src.value) {}
			Component<C> &operator=(Component<C> src) {
				value = src.value;
				return *this;
			}
			
			// Compound assignment operators.
			Component<C> &operator+=(Component<C> rhs) {
				value += rhs.value;
				return *this;
			}
			Component<C> &operator-=(Component<C> rhs) {
				value -= rhs.value;
				return *this;
			}
			Component<C> &operator*=(Component<C> rhs) {
				value *= rhs.value;
				return *this;
			}
			Component<C> &operator/=(Component<C> rhs) {
				value /= rhs.value;
				return *this;
			}
			Component<C> &operator%=(Component<C> rhs) {
				value %= rhs.value;
				return *this;
			}
			Component<C> &operator&=(Component<C> rhs) {
				value &= rhs.value;
				return *this;
			}
			Component<C> &operator|=(Component<C> rhs) {
				value |= rhs.value;
				return *this;
			}
			Component<C> &operator^=(Component<C> rhs) {
				value ^= rhs.value;
				return *this;
			}
			Component<C> &operator<<=(Component<C> rhs) {
				value <<= rhs.value;
				return *this;
			}
			Component<C> &operator>>=(Component<C> rhs) {
				value >>= rhs.value;
				return *this;
			}
			
			Component<C> operator+(Component<C> other) {
				return Component<C>(*this) += other;
			}
			Component<C> operator-(Component<C> other) {
				return Component<C>(*this) -= other;
			}
			Component<C> operator*(Component<C> other) {
				return Component<C>(*this) *= other;
			}
			Component<C> operator/(Component<C> other) {
				return Component<C>(*this) /= other;
			}
			Component<C> operator%(Component<C> other) {
				return Component<C>(*this) %= other;
			}
			Component<C> operator&(Component<C> other) {
				return Component<C>(*this) &= other;
			}
			Component<C> operator|(Component<C> other) {
				return Component<C>(*this) |= other;
			}
			Component<C> operator^(Component<C> other) {
				return Component<C>(*this) ^= other;
			}
			Component<C> operator<<(Component<C> other) {
				return Component<C>(*this) <<= other;
			}
			Component<C> operator>>(Component<C> other) {
				return Component<C>(*this) >>= other;
			}
			
			Component<C> operator+() const {
				return Component<C>(+value);
			}
			Component<C> operator-() const {
				return Component<C>(-value);
			}
			
			Component<C> &operator++() {
				++value;
				return *this;
			}
			Component<C> operator++(int) {
				Component<C> result(*this);
				++value;
				return result;
			}
			Component<C> &operator--() {
				--value;
				return *this;
			}
			Component<C> operator--(int) {
				Component<C> result(*this);
				--value;
				return result;
			}
			
			bool operator==(Component<C> other) const {
				return value == other.value;
			}
			bool operator!=(Component<C> other) const {
				return value != other.value;
			}
			bool operator>(Component<C> other) const {
				return value > other.value;
			}
			bool operator<(Component<C> other) const {
				return value < other.value;
			}
			bool operator>=(Component<C> other) const {
				return value >= other.value;
			}
			bool operator<=(Component<C> other) const {
				return value <= other.value;
			}
			bool operator!() const {
				return !value;
			}
			bool operator&&(Component<C> other) const {
				return value && other.value;
			}
			bool operator||(Component<C> other) const {
				return value || other.value;
			}
			
			/// Value of the component.
			ValueType value;
		};
		
		/// Typedef for easier reading and writing.
		typedef Component<X> XComponent;
		/// Typedef for easier reading and writing.
		typedef Component<Y> YComponent;
		/// Typedef for easier reading and writing.
		typedef Component<Z> ZComponent;
		
		/**
		 * Default constructor.
		 */
		Vector();
		
		/**
		 * Initializes the vector with the given x component.
		 * @param newX X component to use.
		 */
		Vector(XComponent newX);
		
		/**
		 * Initializes the vector with the given x component.
		 * @param newY Y component to use.
		 */
		Vector(YComponent newY);
		
		/**
		 * Initializes the vector with the given x component.
		 * @param newZ Z component to use.
		 */
		Vector(ZComponent newZ);
		
		/**
		 * Initializes the vector with the given x and y components.
		 * @param newX X component to use.
		 * @param newY Y component to use.
		 * @param newZ Z component to use.
		 */
		Vector(XComponent newX, YComponent newY, ZComponent newZ);
		
		/**
		 * Copy constructor.
		 * @param src Vector to make a copy of.
		 */
		Vector(const Vector3 &src);
		
		/**
		 * Assignment operator overload.
		 * @param src Vector to copy.
		 * @return Reference to the modified instance.
		 */
		Vector3 &operator=(const Vector3 &src);
		
		/**
		 * Checks wether or not the given vector is equal. Two vectors are said
		 * to be equal if their coordinates are equal.
		 * @param other Vector to compare the instance with.
		 * @return True if the coordinates are equal, false if not.
		 */
		bool operator==(const Vector3 &other) const;
		/**
		 * Checks wether or not the given vector is different. Two vectors are
		 * said to be equal if their coordinates are equal.
		 * @param other Vector to compare the instance with.
		 * @return True if at least one coordinate is different, false if not.
		 */
		bool operator!=(const Vector3 &other) const;
		
		Vector3 &operator+=(const Vector3 &other);
		Vector3 &operator+=(ValueType delta);
		Vector3 &operator+=(XComponent xDelta);
		Vector3 &operator+=(YComponent yDelta);
		Vector3 &operator+=(ZComponent zDelta);
		
		Vector3 &operator-=(const Vector3 &other);
		Vector3 &operator-=(ValueType delta);
		Vector3 &operator-=(XComponent xDelta);
		Vector3 &operator-=(YComponent yDelta);
		Vector3 &operator-=(ZComponent zDelta);
		
		Vector3 &operator*=(ValueType delta);
		Vector3 &operator*=(XComponent xDelta);
		Vector3 &operator*=(YComponent yDelta);
		Vector3 &operator*=(ZComponent zDelta);
		
		Vector3 &operator/=(ValueType delta);
		Vector3 &operator/=(XComponent xDelta);
		Vector3 &operator/=(YComponent yDelta);
		Vector3 &operator/=(ZComponent zDelta);
		
		Vector3 operator+(const Vector3 &other) const;
		Vector3 operator+(ValueType delta) const;
		friend Vector3 operator+(ValueType delta, const Vector3 &vector) {
			return Vector3(vector) += delta;
		}
		Vector3 operator+(XComponent xDelta) const;
		friend Vector3 operator+(XComponent xDelta, const Vector3 &vector) {
			return Vector3(vector) += xDelta;
		}
		Vector3 operator+(YComponent yDelta) const;
		friend Vector3 operator+(YComponent yDelta, const Vector3 &vector) {
			return Vector3(vector) += yDelta;
		}
		Vector3 operator+(ZComponent zDelta) const;
		friend Vector3 operator+(ZComponent zDelta, const Vector3 &vector) {
			return Vector3(vector) += zDelta;
		}
		Vector3 operator+() const;
		
		Vector3 operator-(const Vector3 &other) const;
		Vector3 operator-(ValueType delta) const;
		friend Vector3 operator-(ValueType delta, const Vector3 &vector) {
			return Vector3(vector) -= delta;
		}
		Vector3 operator-(XComponent xDelta) const;
		friend Vector3 operator-(XComponent xDelta, const Vector3 &vector) {
			return Vector3(vector) -= xDelta;
		}
		Vector3 operator-(YComponent yDelta) const;
		friend Vector3 operator-(YComponent yDelta, const Vector3 &vector) {
			return Vector3(vector) -= yDelta;
		}
		Vector3 operator-(ZComponent zDelta) const;
		friend Vector3 operator-(ZComponent zDelta, const Vector3 &vector) {
			return Vector3(vector) -= zDelta;
		}
		Vector3 operator-() const;
		
		/**
		 * Calculates the dot product.
		 * @param other Other vector to use to calculate the dot product.
		 * @return Resulting dot product.
		 * @see BaconBox::Vector::getDotProduct()
		 */
		ValueType operator*(const Vector3 &other) const;
		
		Vector3 operator*(ValueType delta) const;
		friend Vector3 operator*(ValueType delta, const Vector3 &vector) {
			return Vector3(vector) *= delta;
		}
		Vector3 operator*(XComponent xDelta) const;
		friend Vector3 operator*(XComponent xDelta, const Vector3 &vector) {
			return Vector3(vector) *= xDelta;
		}
		Vector3 operator*(YComponent yDelta) const;
		friend Vector3 operator*(YComponent yDelta, const Vector3 &vector) {
			return Vector3(vector) *= yDelta;
		}
		Vector3 operator*(ZComponent zDelta) const;
		friend Vector3 operator*(ZComponent zDelta, const Vector3 &vector) {
			return Vector3(vector) *= zDelta;
		}
		
		Vector3 operator/(ValueType delta) const;
		friend Vector3 operator/(ValueType delta, const Vector3 &vector) {
			return Vector3(vector) /= delta;
		}
		Vector3 operator/(XComponent xDelta) const;
		friend Vector3 operator/(XComponent xDelta, const Vector3 &vector) {
			return Vector3(vector) /= xDelta;
		}
		Vector3 operator/(YComponent yDelta) const;
		friend Vector3 operator/(YComponent yDelta, const Vector3 &vector) {
			return Vector3(vector) /= yDelta;
		}
		Vector3 operator/(ZComponent zDelta) const;
		friend Vector3 operator/(ZComponent zDelta, const Vector3 &vector) {
			return Vector3(vector) /= zDelta;
		}
		
		/**
		 * Calculates the instance's length. Also known as the magnitude or the
		 * norm.
		 * @return Instance's length.
		 */
		ValueType getLength() const;
		
		/**
		 * Changes the vector's length.
		 * @param newLength New length to set to the vector.
		 */
		void setLength(ValueType newLength);
		
		/**
		 * Calculates the instance's squared length.
		 * @return Instance's length.
		 */
		ValueType getSquaredLength() const;
		
		/**
		 * Calculates the dot product between the instance and another vector.
		 * @param other Other vector used to calculate the dot product.
		 * @return Resulting dot product.
		 */
		ValueType getDotProduct(const Vector3 &other) const;
		
		/**
		 * Gets a normalized version of the instance. Same as doing
		 * setLength(1) on a copy of the instance.
		 * @return Copy of the instance, but normalized.
		 */
		Vector3 getNormalized() const;
		
		/**
		 * Normalizes the instance. Same as calling setLength(1).
		 */
		void normalize();
		
		/**
		 * Serializes the instance to a Value.
		 * @param node Value to serialize the Vector2T to.
		 * @param setName Wether or not we need to set the name.
		 * @see BaconBox::DefaultSerializer
		 */
		void serialize(Value &node, bool setName = true) const {
			if (setName) {
				node.setName("Vector3");
			}
			
			// We set the value's attributes correctly.
			node["x"].setDouble(static_cast<double>(x));
			node["x"].setAttribute(true);
			node["y"].setDouble(static_cast<double>(y));
			node["y"].setAttribute(true);
			node["z"].setDouble(static_cast<double>(z));
			node["z"].setAttribute(true);
		}
		
		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to deserialize the value from.
		 * @see BaconBox::DefaultSerializer
		 */
		bool deserialize(const Value &node) {
			bool result = true;
			
			// The vector can either be an array of two values or an object
			// with the x and y members.
			if (node.getArray().size() == 3) {
				x = static_cast<ValueType>(node.getArray()[0].getDouble());
				y = static_cast<ValueType>(node.getArray()[1].getDouble());
				z = static_cast<ValueType>(node.getArray()[2].getDouble());
			} else {
				Object::const_iterator itX = node.getObject().find("x");
				Object::const_iterator itY = node.getObject().find("y");
				Object::const_iterator itZ = node.getObject().find("z");
				
				// We make sure the value contains the "x", "y" and "z" values.
				if (itX != node.getObject().end() &&
				    itY != node.getObject().end() &&
					itZ != node.getObject().end() &&
				    itX->second.isNumeric() && itY->second.isNumeric() && itZ->second.isNumeric()) {
					
					x = static_cast<ValueType>(itX->second.getDouble());
					y = static_cast<ValueType>(itY->second.getDouble());
					z = static_cast<ValueType>(itZ->second.getDouble());
					
				} else {
					result = false;
				}
			}
			
			return result;
		}
		
		/**
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize a Vector2T.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		static bool isValidValue(const Value &node) {
			Object::const_iterator itX = node.getObject().find("x");
			Object::const_iterator itY = node.getObject().find("y");
			Object::const_iterator itZ = node.getObject().find("z");
			
			return node.getArray().size() == 3 || (itX != node.getObject().end() && itY != node.getObject().end() && itZ != node.getObject().end() &&
												   itX->second.isNumeric() && itY->second.isNumeric() && itZ->second.isNumeric());
			
		}
		
		/**
		 * X coordinate. Positive values increase towards the right, while
		 * negative values decrease towards the left.
		 */
		ValueType x;
		
		/**
		 * Y coordinate. Positive values increase towards the bottom, while
		 * negative values decrease towards the top.
		 */
		ValueType y;
		
		/**
		 * Y coordinate. Positive values increase towards the bottom, while
		 * negative values decrease towards the top.
		 */
		ValueType z;
	private:
	};
	
	template <typename T>
	Vector<T, 3u>::Vector() : x(ZERO), y(ZERO), z(ZERO) {}
	template <typename T>
	Vector<T, 3u>::Vector(XComponent newX) : x(newX.value), y(ZERO) {}
	template <typename T>
	Vector<T, 3u>::Vector(YComponent newY) : x(ZERO), y(newY.value) {}
	template <typename T>
	Vector<T, 3u>::Vector(ZComponent newZ) : x(ZERO), y(ZERO), z(newZ.value) {}
	template <typename T>
	Vector<T, 3u>::Vector(XComponent newX, YComponent newY, ZComponent newZ) : x(newX.value), y(newY.value), z(newZ.value) {}
	template <typename T>
	Vector<T, 3u>::Vector(const Vector3 &src) : x(src.x), y(src.y), z(src.z) {}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator=(const Vector3 &src) {
		x = src.x;
		y = src.y;
		z = src.z;
		return *this;
	}
	template <typename T>
	bool Vector<T, 3u>::operator==(const Vector3 &other) const {
		return x == other.x && y == other.y && z == other.z;
	}
	template <typename T>
	bool Vector<T, 3u>::operator!=(const Vector3 &other) const {
		return x != other.x || y != other.y || z != other.z;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator+=(const Vector3 &other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator+=(ValueType delta) {
		x += delta;
		y += delta;
		z += delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator+=(XComponent xDelta) {
		x += xDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator+=(YComponent yDelta) {
		y += yDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator+=(ZComponent zDelta) {
		z += zDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator-=(const Vector3 &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator-=(ValueType delta) {
		x -= delta;
		y -= delta;
		z -= delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator-=(XComponent xDelta) {
		x -= xDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator-=(YComponent yDelta) {
		y -= yDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator-=(ZComponent zDelta) {
		z -= zDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator*=(ValueType delta) {
		x *= delta;
		y *= delta;
		z *= delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator*=(XComponent xDelta) {
		x *= xDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator*=(YComponent yDelta) {
		y *= yDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator*=(ZComponent zDelta) {
		z *= zDelta.value;
		return *this;
	}
	
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator/=(ValueType delta) {
		x /= delta;
		y /= delta;
		z /= delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator/=(XComponent xDelta) {
		x /= xDelta.value;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator/=(YComponent yDelta) {
		y /= yDelta.value;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 &Vector<T, 3u>::operator/=(ZComponent zDelta) {
		z /= zDelta.value;
	}
	
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator+(const Vector3 &other) const {
		return Vector3(*this) += other;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator+(ValueType delta) const {
		return Vector3(*this) += delta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator+(XComponent xDelta) const {
		return Vector3(*this) += xDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator+(YComponent yDelta) const {
		return Vector3(*this) += yDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator+(ZComponent zDelta) const {
		return Vector3(*this) += zDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator+() const {
		return Vector3(+x, +y, +z);
	}
	
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator-(const Vector3 &other) const {
		return Vector3(*this) -= other;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator-(ValueType delta) const {
		return Vector3(*this) -= delta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator-(XComponent xDelta) const {
		return Vector3(*this) -= xDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator-(YComponent yDelta) const {
		return Vector3(*this) -= yDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator-(ZComponent zDelta) const {
		return Vector3(*this) -= zDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator-() const {
		return Vector3(-x, -y, -z);
	}
	
	template <typename T>
	typename Vector<T, 3u>::ValueType Vector<T, 3u>::operator*(const Vector3 &other) const {
		return getDotProduct(other);
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator*(ValueType delta) const {
		return Vector3(*this) *= delta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator*(XComponent xDelta) const {
		return Vector3(*this) *= xDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator*(YComponent yDelta) const {
		return Vector3(*this) *= yDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator*(ZComponent zDelta) const {
		return Vector3(*this) *= zDelta;
	}
	
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator/(ValueType delta) const {
		return Vector3(*this) /= delta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator/(XComponent xDelta) const {
		return Vector3(*this) /= xDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator/(YComponent yDelta) const {
		return Vector3(*this) /= yDelta;
	}
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::operator/(ZComponent zDelta) const {
		return Vector3(*this) /= zDelta;
	}
	
	template <typename T>
	typename Vector<T, 3u>::ValueType Vector<T, 3u>::getLength() const {
		return std::sqrt(getDotProduct(*this));
	}
	
	template <typename T>
	void Vector<T, 3u>::setLength(ValueType newLength) {
		normalize();
		this->operator*=(newLength);
	}
	
	template <typename T>
	typename Vector<T, 3u>::ValueType Vector<T, 3u>::getSquaredLength() const {
		return getDotProduct(*this);
	}
	
	template <typename T>
	typename Vector<T, 3u>::ValueType Vector<T, 3u>::getDotProduct(const Vector3 &other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	
	template <typename T>
	typename Vector<T, 3u>::Vector3 Vector<T, 3u>::getNormalized() const {
		return *this / getLength();
	}
	
	template <typename T>
	void Vector<T, 3u>::normalize() {
		this->operator/=(getLength());
	}
	
	template <typename T>
	std::ostream &operator<<(std::ostream &output, const Vector<T, 3u>& v) {
		Value tmpValue;
		DefaultSerializer::serialize(v, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}

	typedef Vector<float, 3u> Vector3;
}

#endif