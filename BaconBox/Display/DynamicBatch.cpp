#include "DynamicBatch.h"

#include "BaconBox/Console.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include <limits>
namespace BaconBox {
	DynamicBatch::DynamicBatch():indiceIterator(0) {
		int reserveSize = std::numeric_limits<uint16_t>::max();
		colors.reserve(reserveSize);
		colorOffsets.reserve(reserveSize);
		textureCoordinates.reserve(reserveSize);
		vertices.reserve(reserveSize);
		indices.reserve(reserveSize);
	
	}

	DynamicBatch::~DynamicBatch() {
	}

	void DynamicBatch::prepareRender() {
		this->vertices.resize(0);
		this->textureCoordinates.resize(0);
		this->colors.resize(0);
		this->colorOffsets.resize(0);
		this->indices.resize(0);
	}

	void DynamicBatch::addItem(const VertexArray &newVertices, const Color &newColor,
                            const Color &newColorOffset, const TextureCoordinates &newTextureCoordinates) {
            for(int i = 0; i<4; i++){
				this->colors.push_back(newColor);
				colorOffsets.push_back(newColorOffset);
				vertices.pushBack(newVertices[i]);
				textureCoordinates.push_back(newTextureCoordinates[i]);
            }
		this->indices.push_back(indiceIterator);
		this->indices.push_back(++indiceIterator);
		this->indices.push_back(++indiceIterator);
		this->indices.push_back(++indiceIterator);
		this->indices.push_back(indiceIterator);
		this->indices.push_back(++indiceIterator);
	}

	
	
	void DynamicBatch::render(GraphicDriver *driver, const TextureInformation *textureInformation, bool blend) {
		this->indices.pop_back();
		indiceIterator = 0;
		driver->drawBatchWithTextureColorColorOffset(this->vertices, textureInformation, this->textureCoordinates, this->indices, this->colors, this->colorOffsets, blend);
    }



	const StandardVertexArray &DynamicBatch::getVertices() const {
		return this->vertices;
	}

	const TextureCoordinates &DynamicBatch::getTextureCoordinates() const {
		return this->textureCoordinates;
	}

	const Color &DynamicBatch::getColor() const {
		return this->colors.front();
	}

}
