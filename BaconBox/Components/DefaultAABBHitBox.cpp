#include "DefaultAABBHitBox.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Console.h"

namespace BaconBox {

	DefaultAABBHitBox::DefaultAABBHitBox(): AABBHitBox(), mesh(NULL), entityContainer(NULL) {
		this->initializeConnections();
	}
	
	DefaultAABBHitBox::DefaultAABBHitBox(const DefaultAABBHitBox &src) : AABBHitBox(src), mesh(NULL), entityContainer(NULL) {
		this->initializeConnections();
	}
	
	DefaultAABBHitBox &DefaultAABBHitBox::operator=(const DefaultAABBHitBox &src) {
		this->AABBHitBox::operator=(src);
		
		return *this;
	}
	
	DefaultAABBHitBox *DefaultAABBHitBox::clone() const {
		return new DefaultAABBHitBox(*this);
	}

	void DefaultAABBHitBox::initializeConnections() {
		this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
		this->addConnection(new ComponentConnection<Mesh>(&this->mesh));
	}

	const AxisAlignedBoundingBox &DefaultAABBHitBox::getAABB() {
		if (!haveCustomAABB) {
			if (!mesh) {
				for (int i = 0; i < entityContainer->getNbChildren(); i++) {
					MovieClipEntity *child =  entityContainer->getChildAt(i);
					AxisAlignedBoundingBox childAABB = child->getAABB();

					if (i != 0) {
						if (childAABB.getLeft() < customAABB.getLeft()) {
							customAABB.setXPosition(childAABB.getXPosition());
						}

						if (childAABB.getTop() < customAABB.getTop()) {
							customAABB.setYPosition(childAABB.getYPosition());
						}

						if (childAABB.getRight() > customAABB.getRight()) {
							customAABB.setWidth(childAABB.getWidth());
						}

						if (childAABB.getBottom() > customAABB.getBottom()) {
							customAABB.setHeight(childAABB.getHeight());
						}

					} else {
						customAABB = childAABB;
					}

				}

			} else if (mesh) {
				customAABB = mesh->getPostTransformVertices().getAxisAlignedBoundingBox();
			}
		}

		return customAABB;
	}
}