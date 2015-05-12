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
	    friend class EntityFactory;
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

		void setMatrix(const Matrix2D & m);
		Matrix2D & getMatrix();
		Matrix2D getConcatMatrix();
		void setFrameMatrix(int frame);
	protected:
		void initializeConnections();
	private:
void internalSetMatrix(const Matrix2D & m);
		Matrix2D matrix;
		Matrix2D concatMatrix;
		std::map<int, Matrix2D> * matrixByParentFrame;
		EntityContainer * entityContainer;
		void updateMatrix(VMATH_NAMESPACE::Vector2f position, VMATH_NAMESPACE::Vector2f scale, float angle);
		bool hasCustomMatrix;
	};
}

#endif
