#include "MeshDriverRenderer.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Components/ColorFilter.h"
#include "BaconBox/Components/Texture.h"

namespace BaconBox {
	BB_ID_IMPL(MeshDriverRenderer);

	int MeshDriverRenderer::MESSAGE_GET_RENDER_MODE = IDManager::generateID();
	int MeshDriverRenderer::MESSAGE_SET_RENDER_MODE = IDManager::generateID();

	MeshDriverRenderer::MeshDriverRenderer(int newRenderMode) : Component(), mesh(NULL), texture(NULL), colorFilter(NULL), renderMode(newRenderMode) {
	}

	MeshDriverRenderer::MeshDriverRenderer(const MeshDriverRenderer &src) : Component(src), mesh(NULL), texture(NULL), colorFilter(NULL), renderMode(src.renderMode) {
	}

	MeshDriverRenderer::~MeshDriverRenderer() {
	}

	MeshDriverRenderer &MeshDriverRenderer::operator=(const MeshDriverRenderer &src) {
		if (this != &src) {
			this->mesh = NULL;
			this->texture = NULL;
			this->colorFilter = NULL;

			this->renderMode = src.renderMode;
		}

		return *this;
	}

	MeshDriverRenderer *MeshDriverRenderer::clone() const {
		return new MeshDriverRenderer(*this);
	}

	void MeshDriverRenderer::receiveMessage(int senderID, int destID, int message, void *data) {
		if (destID == MeshDriverRenderer::ID) {
			return;
		}

		if (message == MeshDriverRenderer::MESSAGE_GET_RENDER_MODE) {
			*reinterpret_cast<int *>(data) = this->getRenderMode();

		} else if (message == MeshDriverRenderer::MESSAGE_SET_RENDER_MODE) {
			this->setRenderMode(*reinterpret_cast<int *>(data));
		}
	}

	void MeshDriverRenderer::render() {
		// We check if we have to render a shape.
		if (this->renderMode & RenderMode::SHAPE) {
			// We make sure we are attached to an entity.
			Entity *entity = this->getEntity();
			if (entity) {
				// We make sure we have vertices.
				if (!this->mesh) {
					this->mesh = reinterpret_cast<Mesh *>(entity->getComponent(Mesh::ID));
				}
				
				if (this->mesh) {
					Color color = Color::WHITE;
					// We check if we have a color (if not, it will be defaulted to white).
					if (this->renderMode & RenderMode::COLOR) {
						if (!this->colorFilter) {
							this->colorFilter = reinterpret_cast<ColorFilter *>(entity->getComponent(ColorFilter::ID));
						}
						
						if (this->colorFilter) {
							color = this->colorFilter->getColor();
						}
					}
					
					// We check if we have to render a texture on the shape.
					if (this->renderMode & RenderMode::TEXTURE) {
						if (!this->texture) {
							this->texture = reinterpret_cast<Texture *>(entity->getComponent(Texture::ID));
						}
						
						if (this->texture) {
							// We render with the texture.
							GraphicDriver::getInstance().drawShapeWithTextureAndColor(this->mesh->getVertices(), this->texture->getTexture(), this->texture->getTextureCoordinates(), color);
						} else {
							// We render without the texture.
							GraphicDriver::getInstance().drawShapeWithColor(this->mesh->getVertices(), color);
						}
					} else {
						// We render the mesh with the given color.
						GraphicDriver::getInstance().drawShapeWithColor(this->mesh->getVertices(), color);
					}
				}
			}
		}
	}

	int MeshDriverRenderer::getRenderMode() const {
		return this->renderMode;
	}

	void MeshDriverRenderer::setRenderMode(int newRenderMode) {
		this->renderMode = newRenderMode;
	}
}
