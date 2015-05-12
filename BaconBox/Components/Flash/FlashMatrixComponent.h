#ifndef BB_FLASHMATRIXCOMPONENT_H
#define BB_FLASHMATRIXCOMPONENT_H

#include "BaconBox/Core/Component.h"

#include "BaconBox/Components/MatrixComponent.h"
#include "BaconBox/vmath.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Matrix2D.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Flash/MovieClipHolder.h"

namespace BaconBox {
	
	class Transform;
	
	/**
	 * Component that manages the entity's position, orientation and scaling
	 * values.
	 */
	class FlashMatrixComponent : public MatrixComponent {
	public:
		BB_ID_HEADER;

		FlashMatrixComponent();


		void setMatrix(const Matrix2D &m);

		virtual Matrix2D &getMatrix();
		virtual Matrix2D getConcatMatrix();

	protected:
		void initializeConnections();
		Matrix2D matrix;
		Matrix2D concatMatrix;
		MovieClipHolder *movieClipHolder;

	};

}

#endif
