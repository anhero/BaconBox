#ifndef BB_MATRIXCOMPONENT_H
#define BB_MATRIXCOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/vmath.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Matrix2D.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	
	class Transform;
	
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class MatrixComponent : public Component {
	public:
		BB_ID_HEADER;
		static int MESSAGE_MATRIX_CHANGED;

		MatrixComponent();

		virtual void setMatrix(const Matrix2D &m);
		virtual Matrix2D &getMatrix() = 0;
		virtual Matrix2D getConcatMatrix() = 0;

	protected:
		void initializeConnections();
		Transform *transform;
	};

	class MatrixComponentProxy : public ComponentProxy {
	public:
		MatrixComponentProxy(Entity *entity);
		MatrixComponent *getMatrixComponent();
		void setMatrix(const Matrix2D &m);
		Matrix2D &getMatrix();
		Matrix2D getConcatMatrix();

	protected:
		void setMatrixComponent(MatrixComponent *matrixComponent);

	};
}

#endif
