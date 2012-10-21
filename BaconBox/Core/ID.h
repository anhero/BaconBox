#ifndef BB_ID_H
#define BB_ID_H

namespace BaconBox {
	class IDImplementation {
	private:
		template <typename T> friend class ID;
		static int getNextId();
	};
	
	template <typename T>
	class ID : private IDImplementation {
	public:
		static int getId() {
			return ID<T>::id;
		}
	private:
		static int id;
	};
	
	template <typename T>
	int ID<T>::id = IDImplementation::getNextId();
}
#endif
