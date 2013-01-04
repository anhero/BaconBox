/**
 * @file
 * @ingroup Helper
 */
#ifndef BB_CALL_HELPER_H
#define BB_CALL_HELPER_H

namespace BaconBox {
	template <typename T, typename U, bool CALL>
	struct CallUpdate {
		void operator() (T *) {
		}
	};

	template <typename T, typename U>
	struct CallUpdate<T, U, true> {
		void operator() (T *ptr) {
			ptr->U::update();
		}
	};

	template <typename T, bool CALL>
	struct CallSetToBeDeleted {
		void operator() (bool, T *) {
		}
	};

	template <typename T>
	struct CallSetToBeDeleted<T, true> {
		void operator() (bool newToBeDeleted, T *ptr) {
			ptr->setToBeDeleted(newToBeDeleted);
		}
	};
}

#endif // BB_CALL_HELPER_H
