#include "MeshDriverRenderer.h"
#include "BaconBox/Console.h"

#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Display/StandardRenderer/Driver/GraphicDriver.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Components/DefaultColorTransform.h"
#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Components/Visibility.h"
#include "BaconBox/Console.h"
#include "BaconBox/ResourceManager.h"
namespace BaconBox {
	BB_ID_IMPL(MeshDriverRenderer);

	int MeshDriverRenderer::MESSAGE_GET_RENDER_MODE = IDManager::generateID();
	int MeshDriverRenderer::MESSAGE_SET_RENDER_MODE = IDManager::generateID();

	MeshDriverRenderer::MeshDriverRenderer(int newRenderMode,int degenerationStride, int degenerationJump) : Component(), mesh(NULL), texture(NULL), colorTransform(NULL), visibility(NULL), renderMode(newRenderMode), colorMultiplier(Color::WHITE), colorOffset(Color::NO_COLOR), color(Color::WHITE), graphicDriver(&GraphicDriver::getInstance()), degenerationStride(degenerationStride), degenerationJump(degenerationJump) {
		this->initializeConnections();
	}

	MeshDriverRenderer::MeshDriverRenderer(const MeshDriverRenderer &src) : Component(src), mesh(NULL), texture(NULL), colorTransform(NULL), visibility(NULL), colorMultiplier(src.colorMultiplier), colorOffset(src.colorOffset),renderMode(src.renderMode), graphicDriver(&GraphicDriver::getInstance()) {
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

	void MeshDriverRenderer::update() {


		if (!this->visibility || this->visibility->isVisible()) {
			// We check if we have to render a shape.
			if (this->renderMode & RenderMode::SHAPE) {
				// We make sure we are attached to an entity.
				Entity *entity = this->getEntity();
				if (entity) {
					if (this->mesh) {


						if(this->colorTransform){
							if (this->renderMode & RenderMode::COLOR_TRANSORMED){
								ColorMatrix &  matrix = this->colorTransform->getConcatColorMatrix();
								color = matrix.getPreMultipliedColor(this->colorTransform->getColor());
								colorOffset = matrix.colorOffset;
							}
							else if(this->renderMode & RenderMode::COLOR){
								color = this->colorTransform->getColor();
								colorOffset = Color::NO_COLOR;
							}
							else{
								color = Color::WHITE;
								colorOffset = Color::NO_COLOR;
							}
						}

						// We check if we have to render a texture on the shape.
						if (this->renderMode & RenderMode::TEXTURE) {
							if (this->texture) {
								if(! this->texture->getTexture()->isLoaded()){
									ResourceManager::loadTexture(this->texture->getTexture());
								}

								// We render with the texture.
								if(color == Color::WHITE && colorOffset == Color::NO_COLOR){
									graphicDriver->drawShapeWithTexture(this->mesh->getPostTransformVertices(), this->texture->getTexture(), this->texture->getTextureCoordinates(), (this->renderMode & RenderMode::BLENDED), degenerationStride, degenerationJump);

								}
								else{
									if (this->texture->getTextureCoordinates().size() > 0) {
										graphicDriver->drawShapeWithTextureColorColorOffset(this->mesh->getPostTransformVertices(), this->texture->getTexture(), this->texture->getTextureCoordinates(), color, colorOffset, (this->renderMode & RenderMode::BLENDED), degenerationStride, degenerationJump);
									}
#ifdef BB_DEBUG
									else {
										Console::println("Skipping rendering; No texture coordinates for Mesh for Entity of type `"
														 + this->getEntity()->getEntityName() + "`."
														 );
									}
#endif
								}
							} else {
								// We render without the texture.
								Console::error("Rendering mesh with RenderMode::TEXTURE, but without texture not implemented.");
							}
						} else {
							graphicDriver->drawShapeWithColorColorOffset(
										this->mesh->getPostTransformVertices(),
										color, colorOffset,
										(this->renderMode & RenderMode::BLENDED),
										degenerationStride, degenerationJump
										);
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
