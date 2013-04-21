#include "BatchRenderer.h"

#include "BaconBox/Console.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/ComponentConnection.h"

namespace BaconBox {
	BatchRenderer::BatchRenderer() : Component(), sizes(), vertices(), colors(), indices(), indiceList() {
		this->initializeConnections();
	}
	
	BatchRenderer::BatchRenderer(const BatchRenderer &src) : Component(src), sizes(src.sizes), vertices(src.vertices), colors(src.colors), indices(src.indices), indiceList(src.indiceList) {
		this->initializeConnections();
	}
	
	BatchRenderer::~BatchRenderer() {
	}
	
	BatchRenderer &BatchRenderer::operator=(const BatchRenderer &src) {
		if (this != &src) {
			this->sizes = src.sizes;
			this->vertices = src.vertices;
			this->colors = src.colors;
			this->indices = src.indices;
			this->indiceList = src.indiceList;
		}
		
		return *this;
	}
	
	BatchRenderer *BatchRenderer::clone() const {
		return new BatchRenderer(*this);
	}
	
	void BatchRenderer::receiveMessage(int senderID, int destID, int message, void *data) {
	}
	
	void BatchRenderer::prepareRender() {
		this->sizes.clear();
		this->vertices.clear();
		this->indices.clear();
		this->indiceList.clear();
		
		if (this->texture) {
			this->texture->getTextureCoordinates().clear();
		}
	}
	
	void BatchRenderer::addItem(const VertexArray &newVertices, const Color &newColor, const TextureCoordinates &newTextureCoordinates) {
		if (newVertices.getNbVertices() == newTextureCoordinates.size()) {
			this->vertices.insert(this->vertices.getEnd(), newVertices.getBegin(), newVertices.getEnd());
			this->colors.insert(this->colors.end(), newVertices.getNbVertices(), newColor);
			this->sizes.push_back(newVertices.getNbVertices());
			
			if (this->texture) {
				this->texture->getTextureCoordinates().insert(this->texture->getTextureCoordinates().begin(), newTextureCoordinates.begin(), newTextureCoordinates.end());
			}
		} else {
			Console::println("Tried to add an item into an BatchRenderer that doesn't have the same number of vertices and texture coordinates: ");
			Console::print(newVertices.getNbVertices());
			Console::print(" vertices and ");
			Console::print(newTextureCoordinates.size());
			Console::println(" texture coordinates.");
		}
	}
	
	void BatchRenderer::renderBatch() {
		this->refreshIndices();
		
		if (this->texture) {
			GraphicDriver::getInstance().drawBatchWithTextureAndColor(this->vertices, this->texture->getTexture(), this->texture->getTextureCoordinates(), this->indices, this->indiceList, this->colors);
		}
	}
	
	void BatchRenderer::refreshIndices() {
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
	
	void BatchRenderer::initializeConnections() {
		this->addConnection(new ComponentConnection<Texture>(&this->texture));
		this->refreshConnections();
	}
}
