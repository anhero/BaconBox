#ifndef BB_VALUE_CHANGED_DATA_H
#define BB_VALUE_CHANGED_DATA_H

namespace BaconBox {
	template<typename T>
	struct ValueChangedData {
		/**
		 * Default constructor. Uses the T's default constructor.
		 */
		ValueChangedData() : oldValue(), newValue() {
		}

		/**
		 * Parameterized constructor.
		 * @param oldValue Old value to use.
		 * @param newValue New value to use.
		 */
		ValueChangedData(const T &oldValue, const T &newValue) : oldValue(oldValue), newValue(newValue) {
		}

		/**
		 * Copy constructor.
		 * @param src ValueChangedData to make a copy of.
		 */
		ValueChangedData(const ValueChangedData<T> &src) : oldValue(src.oldValue), newValue(src.newValue) {
		}

		/**
		 * Assignment operator overload.
		 * @param src ValueChangedData to copy.
		 * @return Current instance.
		 */
		ValueChangedData &operator=(const ValueChangedData &src) {
			if (this != &src) {
				this->oldValue = src.oldValue;
				this->newValue = src.newValue;
			}

			return *this;
		}

		/// Value before the change.
		T oldValue;
		/// Value after the change.
		T newValue;
	};
}

#endif
