#include "DynamicBatch.h"

#include "BaconBox/Console.h"
#include "BaconBox/Display/StandardRenderer/Driver/GraphicDriver.h"
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
	
	void DynamicBatch::addItem(const VertexArray &newVertices,
							   const TextureCoordinates &newTextureCoordinates,
							   int degenerationStride, int degenerationJump) {
		int size = newVertices.getNbVertices();
		
		for(int i = 0; i< size; i++){
			vertices.pushBack(newVertices[i]);
			textureCoordinates.push_back(newTextureCoordinates[i]);
		}
		
		createNextIndices(size, degenerationStride, degenerationJump);
	}

	void DynamicBatch::addItem(const VertexArray &newVertices,
							   const Color &newColor, const Color &newColorOffset,
							   const TextureCoordinates &newTextureCoordinates,
							   int degenerationStride, int degenerationJump) {
		// Only insert color-specific stuff here.
		for(int i = 0; i < newVertices.getNbVertices(); i++){
			colors.push_back(newColor);
			colorOffsets.push_back(newColorOffset);
		}
		// Everything else is handed out to the other addItem()
		addItem(newVertices, newTextureCoordinates, degenerationStride, degenerationJump);
	}

	void DynamicBatch::createNextIndices(int size, int degenerationStride, int degenerationJump){
		this->indices.push_back(indiceIterator);
		bool skipDegeneration = (degenerationStride >= size || degenerationStride == 0);
		int degenerationCount =0;
		int i = indiceIterator;
		int maxSize = size -1+indiceIterator;
		while (i < (maxSize)) {
			if(skipDegeneration || degenerationStride-1 != degenerationCount){
				this->indices.push_back(++indiceIterator);
				degenerationCount++;
			}
			else{
				degenerationCount =0;
				this->indices.push_back(indiceIterator);
				indiceIterator += degenerationJump;
				this->indices.push_back(indiceIterator);
				this->indices.push_back(indiceIterator);

			}
			i = indiceIterator;
		}
		this->indices.push_back(indiceIterator);
		this->indices.push_back(++indiceIterator);
	}

	void DynamicBatch::render(GraphicDriver *driver, const TextureInformation *textureInformation, bool blend) {
		this->indices.pop_back();
		indiceIterator = 0;
		if(colors.size()){
			driver->drawBatchWithTextureColorColorOffset(this->vertices, textureInformation, this->textureCoordinates, this->indices, this->colors, this->colorOffsets, blend);
		}
		else {
			driver->drawBatchWithTexture(this->vertices, textureInformation, this->textureCoordinates, this->indices, blend);
		}
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
