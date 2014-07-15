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

	const AABB &DefaultAABBHitBox::getAABB() {
		if (!haveCustomAABB) {
			if (!mesh) {
				for (int i = 0; i < entityContainer->getNbChildren(); i++) {
					MovieClipEntity *child =  entityContainer->getChildAt(i);
					AABB childAABB = child->getAABB();

					if (i != 0) {
						if (childAABB.getLeft() < customAABB.getLeft()) {
							customAABB.setWidth(customAABB.getWidth() + (customAABB.getXPosition() - childAABB.getXPosition()));
							customAABB.setXPosition(childAABB.getXPosition());
						}

						if (childAABB.getTop() < customAABB.getTop()) {
							customAABB.setHeight(customAABB.getHeight() + (customAABB.getYPosition() - childAABB.getYPosition()));
							customAABB.setYPosition(childAABB.getYPosition());
						}

						if (childAABB.getRight() > customAABB.getRight()) {
							customAABB.setWidth(childAABB.getRight() - customAABB.getLeft());
						}

						if (childAABB.getBottom() > customAABB.getBottom()) {
							customAABB.setHeight(childAABB.getBottom() - customAABB.getYPosition());
						}

					} else {
						customAABB = childAABB;
					}

				}

			} else if (mesh) {
				customAABB = mesh->getPostTransformVertices().getAABB();
			}
		}

		return customAABB;
	}
}