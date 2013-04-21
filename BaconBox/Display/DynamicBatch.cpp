#include "DynamicBatch.h"

#include "BaconBox/Console.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"

namespace BaconBox {
	DynamicBatch::DynamicBatch() {
	}

	DynamicBatch::~DynamicBatch() {
	}
	
	void DynamicBatch::prepareRender() {
		this->sizes.clear();
		this->vertices.clear();
		this->textureCoordinates.clear();
		this->colors.clear();
		this->indices.clear();
		this->indiceList.clear();
	}
	
	void DynamicBatch::addItem(const VertexArray &newVertices, const Color &newColor, const TextureCoordinates &newTextureCoordinates) {
		if (newVertices.getNbVertices() == newTextureCoordinates.size()) {
			this->vertices.insert(this->vertices.getEnd(), newVertices.getBegin(), newVertices.getEnd());
			this->colors.insert(this->colors.end(), newVertices.getNbVertices(), newColor);
			this->sizes.push_back(newVertices.getNbVertices());
			this->textureCoordinates.insert(this->textureCoordinates.begin(), newTextureCoordinates.begin(), newTextureCoordinates.end());

		} else {
			Console::println("Tried to add an item into an BatchRenderer that doesn't have the same number of vertices and texture coordinates: ");
			Console::print(newVertices.getNbVertices());
			Console::print(" vertices and ");
			Console::print(newTextureCoordinates.size());
			Console::println(" texture coordinates.");
		}
	}
	
	void DynamicBatch::render(GraphicDriver *driver, const TextureInformation *textureInformation) {
		this->refreshIndices();
		driver->drawBatchWithTextureAndColor(this->vertices, textureInformation, this->textureCoordinates, this->indices, this->indiceList, this->colors);
	}
	
	bool DynamicBatch::isSingle() const {
		return this->sizes.size() == 1;
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
	
	void DynamicBatch::refreshIndices() {
		static const StandardVertexArray::SizeType MAX_NB_INDICES = static_cast<StandardVertexArray::SizeType>(std::numeric_limits<IndiceArray::value_type>::max());
		
		// We clear the current indices.
		indices.clear();
		indiceList.clear();
		
		// We calculate the number of indices we'll need in the array.
		IndiceArray::size_type nbIndices = 0;
		
		for (std::vector<VertexArray::SizeType>::const_iterator i = this->sizes.begin(); i != this->sizes.end(); ++i) {
			nbIndices += *i;
		}
		
		// We reserve the necessary memory.
		if (indices.capacity() < nbIndices) {
			indices.reserve(nbIndices);
		}
		
		IndiceArray::value_type indiceIterator = 0;
		
		indiceList.push_back(std::make_pair(0, 0));
		
		size_t currentIndex = 0;
		
		// We initialize the indices for each body's vertices.
		for (std::vector<VertexArray::SizeType>::const_iterator i = this->sizes.begin(); i != this->sizes.end(); ++i) {
			
			// We make sure the body has at least 3 vertices.
			if (*i >= 3) {
				
				// We make sure we aren't over the number of indices in the
				// current batch.
				if ((currentIndex + *i) > indiceList.back().first + MAX_NB_INDICES) {
					this->indiceList.push_back(std::make_pair(currentIndex, indices.size()));
				}
				
				// We get the body's first vertex's indice.
				indiceIterator = static_cast<IndiceArray::value_type>(currentIndex - indiceList.back().first);
				
				// We add the indices for each of the body's triangles.
				IndiceArray::value_type nbTriangles = static_cast<IndiceArray::value_type>(*i - 2);
				
				for (IndiceArray::value_type j = 0; j < nbTriangles; ++j) {
					this->indices.push_back(indiceIterator + j);
					this->indices.push_back(indiceIterator + j);
					this->indices.push_back(indiceIterator + j + 1);
					this->indices.push_back(indiceIterator + j + 2);
					this->indices.push_back(indiceIterator + j + 2);
				}
			}
			
			currentIndex += *i;
		}
	}
}
