#ifndef BB_Batch_H
#define BB_Batch_H

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	class BatchManager;
	
	class Batch : public Component {
	public:
		Batch();
		
		Batch(const Batch &src);
		
		virtual ~Batch();
		
		Batch &operator=(const Batch &src);
		
		virtual Batch *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
	private:
		BatchManager *batch;
		
		size_t identifier;
	};
}

#endif /* defined(BB_Batch_H) */

