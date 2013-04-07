#include "BaconBox/Display/Driver/OpenGL/OpenGLBatchManager.h"

#include <algorithm>
#include <limits>

namespace BaconBox {
	static const VertexArray::SizeType INVALID_INDEX = std::numeric_limits<VertexArray::SizeType>::max();

	OpenGLBatchManager::OpenGLBatchManager() : BatchManager(), firstAvailableIdentifier(0), availableIdentifiers(), indexes(), vertices(), textureCoordinates(), colors(), indices(), indiceList() {
	}

	OpenGLBatchManager::OpenGLBatchManager(const OpenGLBatchManager &src) : BatchManager(src), indexes(src.indexes), textureCoordinates(src.textureCoordinates), colors(src.colors), indices(src.indices), indiceList(src.indiceList) {
	}

	OpenGLBatchManager::~OpenGLBatchManager() {
	}

	OpenGLBatchManager &OpenGLBatchManager::operator=(const OpenGLBatchManager &src) {
		if (this != &src) {
			this->firstAvailableIdentifier = src.firstAvailableIdentifier;
			this->availableIdentifiers = src.availableIdentifiers;
			this->indexes = src.indexes;
			this->textureCoordinates = src.textureCoordinates;
			this->colors = src.colors;
			this->indices = src.indices;
			this->indiceList = src.indiceList;
		}

		return *this;
	}

	void OpenGLBatchManager::setColor(const Color &color, size_t identifier) {
		const VertexArrayInformation &info = this->indexes[identifier];

		std::fill_n(this->colors.begin() + info.index, info.nbVertices, color);
	}

	void OpenGLBatchManager::setTextureCoordinates(const TextureCoordinates &textureCoordinates, size_t identifier) {
		const VertexArrayInformation &info = this->indexes[identifier];

		VertexArray::SizeType nbToCopy = std::min(textureCoordinates.size(), info.nbVertices);

		std::copy(textureCoordinates.begin(), textureCoordinates.begin() + nbToCopy, this->textureCoordinates.begin() + info.index);
	}

	size_t OpenGLBatchManager::addNewVertexArray(VertexArray::SizeType nbVertices, VertexArray::ConstReference defaultValue) {
		size_t newIdentifier = this->getNewIdentifier();
		this->indexes[newIdentifier].index = this->vertices.getNbVertices();
		this->indexes[newIdentifier].nbVertices = nbVertices;

		this->vertices.resize(this->vertices.getNbVertices() + nbVertices, defaultValue);
		this->textureCoordinates.resize(this->vertices.getNbVertices());
		this->colors.resize(this->vertices.getNbVertices(), Color::WHITE);

		this->refreshIndices();

		return newIdentifier;
	}

	size_t OpenGLBatchManager::addNewVertexArray(const VertexArray::ContainerType &newVertices) {
		size_t newIdentifier = this->getNewIdentifier();
		VertexArrayInformation &info = this->indexes[newIdentifier];
		info.index = this->vertices.getNbVertices();
		info.nbVertices = newVertices.size();

		this->vertices.resize(this->vertices.getNbVertices() + info.nbVertices);
		this->textureCoordinates.resize(this->vertices.getNbVertices());
		this->colors.resize(this->vertices.getNbVertices(), Color::WHITE);
		
		std::copy(newVertices.begin(), newVertices.end(), this->vertices.getBegin() + info.index);

		this->refreshIndices();
		
		return newIdentifier;

	}

	void OpenGLBatchManager::removeVertexArray(size_t identifier) {
		const VertexArrayInformation &info = this->indexes[identifier];
		
		this->vertices.erase(this->vertices.getBegin() + info.index, this->vertices.getBegin() + info.index + info.nbVertices);
		this->textureCoordinates.erase(this->textureCoordinates.begin() + info.index, this->textureCoordinates.begin() + info.index + info.nbVertices);
		this->colors.erase(this->colors.begin() + info.index, this->colors.begin() + info.index + info.nbVertices);
		
		this->removeIdentifier(identifier);
		
		this->refreshIndices();
	}

	bool OpenGLBatchManager::containsVertexArray(size_t identifier) const {
		return identifier < this->indexes.size();
	}

	VertexArray::Iterator OpenGLBatchManager::getBegin(size_t identifier) {
		return this->vertices.getBegin() + this->indexes[identifier].index;
	}

	VertexArray::ConstIterator OpenGLBatchManager::getConstBegin(size_t identifier) const {
		return this->vertices.getBegin() + this->indexes[identifier].index;
	}

	VertexArray::Iterator OpenGLBatchManager::getEnd(size_t identifier) {
		return this->vertices.getBegin() + (this->indexes[identifier].index + this->indexes[identifier].nbVertices);
	}

	VertexArray::ConstIterator OpenGLBatchManager::getConstEnd(size_t identifier) const {
		return this->vertices.getBegin() + (this->indexes[identifier].index + this->indexes[identifier].nbVertices);
	}

	VertexArray::ReverseIterator OpenGLBatchManager::getReverseBegin(size_t identifier) {
		return VertexArray::ReverseIterator(this->getEnd(identifier));
	}

	VertexArray::ConstReverseIterator OpenGLBatchManager::getConstReverseBegin(size_t identifier) const {
		return VertexArray::ConstReverseIterator(this->getConstEnd(identifier));
	}

	VertexArray::ReverseIterator OpenGLBatchManager::getReverseEnd(size_t identifier) {
		return VertexArray::ReverseIterator(this->getBegin(identifier));
	}

	VertexArray::ConstReverseIterator OpenGLBatchManager::getConstReverseEnd(size_t identifier) const {
		return VertexArray::ConstReverseIterator(this->getConstBegin(identifier));
	}

	bool OpenGLBatchManager::isEmpty(size_t identifier) const {
		return this->indexes[identifier].nbVertices == 0;
	}

	VertexArray::SizeType OpenGLBatchManager::getNbVertices(size_t identifier) const {
		return this->indexes[identifier].nbVertices;
	}

	void OpenGLBatchManager::clear(size_t identifier) {
		// TODO
	}

	VertexArray::Iterator OpenGLBatchManager::insert(size_t identifier, VertexArray::Iterator position, VertexArray::ConstReference value) {
		// TODO
	}

	void OpenGLBatchManager::insert(size_t identifier, VertexArray::Iterator position, VertexArray::SizeType count, VertexArray::ConstReference value) {
		// TODO
	}

	VertexArray::Iterator OpenGLBatchManager::erase(size_t identifier, VertexArray::Iterator position) {
		// TODO
	}

	VertexArray::Iterator OpenGLBatchManager::erase(size_t identifier, VertexArray::Iterator first, VertexArray::Iterator last) {
		// TODO
	}

	void OpenGLBatchManager::pushBack(size_t identifier, VertexArray::ConstReference newVertex) {
		// TODO
	}

	void OpenGLBatchManager::popBack(size_t identifier) {
		// TODO
	}

	void OpenGLBatchManager::resize(size_t identifier, VertexArray::SizeType count, VertexArray::ConstReference value) {
		// TODO
	}

	void OpenGLBatchManager::refreshIndices() {
		static const StandardVertexArray::SizeType MAX_NB_INDICES = static_cast<StandardVertexArray::SizeType>(std::numeric_limits<IndiceArray::value_type>::max());

		// We clear the current indices.
		indices.clear();
		indiceList.clear();

		// We calculate the number of indices we'll need in the array.
		IndiceArray::size_type nbIndices = 0;

		for (std::vector<VertexArrayInformation>::const_iterator i = this->indexes.begin(); i != this->indexes.end(); ++i) {
			if (i->nbVertices >= 3) {
				nbIndices += (i->nbVertices - 2) * 5 + 1;
			}
		}

		// We reserve the necessary memory.
		indices.reserve(nbIndices);

		IndiceArray::value_type indiceIterator = 0;

		indiceList.push_back(std::make_pair(0, 0));

		// We initialize the indices for each body's vertices.
		for (std::vector<VertexArrayInformation>::const_iterator i = this->indexes.begin(); i != this->indexes.end(); ++i) {

			// We make sure the body has at least 3 vertices.
			if (i->nbVertices >= 3) {

				// We make sure we aren't over the number of indices in the
				// current batch.
				if ((i->index + i->nbVertices) > indiceList.back().first + MAX_NB_INDICES) {
					this->indiceList.push_back(std::make_pair(i->index, indices.size()));
				}

				// We get the body's first vertex's indice.
				indiceIterator = static_cast<IndiceArray::value_type>(i->index - indiceList.back().first);

				// We add the indices for each of the body's triangles.
				IndiceArray::value_type nbTriangles = static_cast<IndiceArray::value_type>(i->nbVertices - 2);

				for (IndiceArray::value_type j = 0; j < nbTriangles; ++j) {
					this->indices.push_back(indiceIterator + j);
					this->indices.push_back(indiceIterator + j);
					this->indices.push_back(indiceIterator + j + 1);
					this->indices.push_back(indiceIterator + j + 2);
					this->indices.push_back(indiceIterator + j + 2);
				}
			}
		}
	}

	size_t OpenGLBatchManager::getNewIdentifier() {
		size_t result;

		if (this->availableIdentifiers.empty()) {
			result = this->indexes.size();
			this->indexes.push_back(VertexArrayInformation());

		} else {
			result = *this->availableIdentifiers.begin();

			this->availableIdentifiers.erase(this->availableIdentifiers.begin());
		}

		return result;
	}

	void OpenGLBatchManager::removeIdentifier(size_t toRemove) {
		if (!this->indexes.empty() && toRemove < this->indexes.size()) {
			if (toRemove == this->indexes.size() - 1) {
				this->indexes.pop_back();

			} else {
				this->availableIdentifiers.insert(toRemove);
			}
		}
	}

	OpenGLBatchManager::VertexArrayInformation::VertexArrayInformation() : index(0u), nbVertices(0u) {
		// TODO
	}

	OpenGLBatchManager::VertexArrayInformation::VertexArrayInformation(VertexArray::SizeType newIndex, VertexArray::SizeType newNbVertices) : index(newIndex), nbVertices(newNbVertices) {
		// TODO
	}

	OpenGLBatchManager::VertexArrayInformation::VertexArrayInformation(const VertexArrayInformation &src) : index(src.index), nbVertices(src.nbVertices) {
		// TODO
	}

	OpenGLBatchManager::VertexArrayInformation &OpenGLBatchManager::VertexArrayInformation::operator=(const VertexArrayInformation &src) {
		if (this != &src) {
			this->index = src.index;
			this->nbVertices = src.nbVertices;
		}

		return *this;
	}
}
