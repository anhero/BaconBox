#include "MeshDriverRenderer.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Components/DefaultColorTransform.h"
#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Visibility.h"

namespace BaconBox {
	BB_ID_IMPL(MeshDriverRenderer);

	int MeshDriverRenderer::MESSAGE_GET_RENDER_MODE = IDManager::generateID();
	int MeshDriverRenderer::MESSAGE_SET_RENDER_MODE = IDManager::generateID();

	MeshDriverRenderer::MeshDriverRenderer(int newRenderMode) : Component(), mesh(NULL), texture(NULL), colorTransform(NULL), visibility(NULL), renderMode(newRenderMode) {
		this->initializeConnections();
	}

	MeshDriverRenderer::MeshDriverRenderer(const MeshDriverRenderer &src) : Component(src), mesh(NULL), texture(NULL), colorTransform(NULL), visibility(NULL), renderMode(src.renderMode) {
		this->initializeConnections();
	}

	MeshDriverRenderer::~MeshDriverRenderer() {
	}

	MeshDriverRenderer &MeshDriverRenderer::operator=(const MeshDriverRenderer &src) {
		if (this != &src) {
			this->mesh = NULL;
			this->texture = NULL;
			this->colorTransform = NULL;

			this->renderMode = src.renderMode;
		}

		return *this;
	}

	MeshDriverRenderer *MeshDriverRenderer::clone() const {
		return new MeshDriverRenderer(*this);
	}

	void MeshDriverRenderer::receiveMessage(int senderID, int destID, int message, void *data) {
		// We make sure to call the parent receiveMessage so the connections are
		// always updated.
		this->Component::receiveMessage(senderID, destID, message, data);

		if (destID == MeshDriverRenderer::ID) {
			if (message == MeshDriverRenderer::MESSAGE_GET_RENDER_MODE) {
				*reinterpret_cast<int *>(data) = this->getRenderMode();

			} else if (message == MeshDriverRenderer::MESSAGE_SET_RENDER_MODE) {
				this->setRenderMode(*reinterpret_cast<int *>(data));
			}
		}
	}

	void MeshDriverRenderer::render() {
		if (!this->visibility || this->visibility->isVisible()) {
			// We check if we have to render a shape.
			if (this->renderMode & RenderMode::SHAPE) {
				// We make sure we are attached to an entity.
				Entity *entity = this->getEntity();
				if (entity) {
					if (this->mesh) {
						Color color = Color::WHITE;
						// We check if we have a color (if not, it will be defaulted to white).
						if (this->renderMode & RenderMode::COLOR) {
							if (this->colorTransform) {
								color = this->colorTransform->getConcatColor();
							}
						}

						// We check if we have to render a texture on the shape.
						if (this->renderMode & RenderMode::TEXTURE) {
							if (this->texture) {
								// We render with the texture.
								GraphicDriver::getInstance().drawShapeWithTextureAndColor(this->mesh->getPostTransformVertices(), this->texture->getTexture(), this->texture->getTextureCoordinates(), color);
							} else {
								// We render without the texture.
								GraphicDriver::getInstance().drawShapeWithColor(this->mesh->getPostTransformVertices(), color);
							}
						} else {
							// We render the mesh with the given color.
							GraphicDriver::getInstance().drawShapeWithColor(this->mesh->getPostTransformVertices(), color);
						}
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

	void MeshDriverRenderer::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<Mesh>(&this->mesh));
		this->addConnection(new ComponentConnection<Texture>(&this->texture));
		this->addConnection(new ComponentConnection<DefaultColorTransform>(&this->colorTransform));
		this->addConnection(new ComponentConnection<Visibility>(&this->visibility));

		this->refreshConnections();
	}
}
