#ifndef BB_DEFAULTMATRIX_H
#define BB_DEFAULTMATRIX_H

#include "BaconBox/Components/MatrixComponent.h"
#include "DefaultEntityContainer.h"

namespace BaconBox {
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class DefaultMatrix : public MatrixComponent {
	public:
		

	
		DefaultMatrix();
		

		/**
		 * Handles the messages received.
		 * @param senderID Type ID of component/entity sending the message.
		 * @param destID Type ID of the component/entity the message is
		 * destined to.
		 * @param data Data used to send or receive any data related to the
		 * message.
		 */
		virtual void receiveMessage(int senderID, int destID, int message, void *data);

		void setMatrix(const Matrix & m);
		Matrix & getMatrix();
		Matrix getConcatMatrix();
	protected:
		void initializeConnections();
	private:
		Matrix matrix;
		EntityContainer * entityContainer;
		void updateMatrix(Vector2 position, Vector2 scale, float angle);
		
	};
}

#endif
