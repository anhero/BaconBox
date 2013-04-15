#ifndef BB_OPEN_GL_STATIC_BATCH_MANAGER_H
#define BB_OPEN_GL_STATIC_BATCH_MANAGER_H

#include <vector>
#include <set>

#include "BaconBox/Display/BatchManager.h"
#include "BaconBox/StandardVertexArray.h"
#include "BaconBox/TextureCoordinates.h"
#include "BaconBox/Display/Driver/IndiceArray.h"
#include "BaconBox/Display/Driver/ColorArray.h"

namespace BaconBox {
	class OpenGLStaticBatchManager : public BatchManager {
	public:
		OpenGLStaticBatchManager();
		
		OpenGLStaticBatchManager(const OpenGLStaticBatchManager &src);
		
		~OpenGLStaticBatchManager();
		
		OpenGLStaticBatchManager &operator=(const OpenGLStaticBatchManager &src);

		void setColor(const Color &color, size_t identifier);
		
		void setTextureCoordinates(const TextureCoordinates &textureCoordinates, size_t identifier);
		
		size_t addNewVertexArray(VertexArray::SizeType nbVertices, VertexArray::ConstReference defaultValue = VertexArray::ValueType());
		
		size_t addNewVertexArray(const VertexArray::ContainerType &newVertices);
		
		void removeVertexArray(size_t identifier);
		
		bool containsVertexArray(size_t identifier) const;
		
		VertexArray::Iterator getBegin(size_t identifier);
		
		VertexArray::ConstIterator getConstBegin(size_t identifier) const;
		
		VertexArray::Iterator getEnd(size_t identifier);
		
		VertexArray::ConstIterator getConstEnd(size_t identifier) const;
		
		VertexArray::ReverseIterator getReverseBegin(size_t identifier);
		
		VertexArray::ConstReverseIterator getConstReverseBegin(size_t identifier) const;
		
		VertexArray::ReverseIterator getReverseEnd(size_t identifier);
		
		VertexArray::ConstReverseIterator getConstReverseEnd(size_t identifier) const;
		
		bool isEmpty(size_t identifier) const;
		
		VertexArray::SizeType getNbVertices(size_t identifier) const;
		
		void clear(size_t identifier);
		
		VertexArray::Iterator insert(size_t identifier, VertexArray::Iterator position, VertexArray::ConstReference value = VertexArray::ValueType());
		
		void insert(size_t identifier, VertexArray::Iterator position, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType());
		
		VertexArray::Iterator erase(size_t identifier, VertexArray::Iterator position);
		
		VertexArray::Iterator erase(size_t identifier, VertexArray::Iterator first, VertexArray::Iterator last);
		
		void pushBack(size_t identifier, VertexArray::ConstReference newVertex);
		
		void popBack(size_t identifier);
		
		void resize(size_t identifier, VertexArray::SizeType count, VertexArray::ConstReference value = VertexArray::ValueType());
	private:
		struct VertexArrayInformation {
			VertexArrayInformation();
			VertexArrayInformation(VertexArray::SizeType newIndex, VertexArray::SizeType newNbVertices);
			VertexArrayInformation(const VertexArrayInformation &src);
			VertexArrayInformation &operator=(const VertexArrayInformation &src);
			VertexArray::SizeType index;
			VertexArray::SizeType nbVertices;
		};
		
		void refreshIndices();
		
		size_t getNewIdentifier();
		
		void removeIdentifier(size_t toRemove);
		
		size_t firstAvailableIdentifier;
		
		std::set<size_t> availableIdentifiers;
		
		std::vector<VertexArrayInformation> indexes;
		
		StandardVertexArray vertices;
		
		TextureCoordinates textureCoordinates;
		
		ColorArray colors;
		
		IndiceArray indices;
		
		IndiceArrayList indiceList;
	};
}

#endif /* defined(BB_OPEN_GL_STATIC_BATCH_MANAGER_H) */