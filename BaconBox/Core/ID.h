#ifndef BB_ID_H
#define BB_ID_H

#define HAS_ID(TYPE) virtual int getId() const { return ID<TYPE>::NUMBER; }

namespace BaconBox {
	class IDImplementation {
	private:
		template <typename T> friend class ID;
		static int getNextId();
	};
	
	template <typename T>
	class ID : private IDImplementation {
	public:
		static const int NUMBER;
	private:
		
		ID();
		ID(const ID &);
	};
	
	template <typename T>
	const int ID<T>::NUMBER = IDImplementation::getNextId();
}
#endif
