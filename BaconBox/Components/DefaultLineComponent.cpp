#include "DefaultLineComponent.h"
#include "BaconBox/Console.h"

#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/Display/SubTextureInfo.h"


namespace BaconBox {
	DefaultLineComponent::DefaultLineComponent(SubTextureInfo * subTexture) : LineComponent(),  mesh(NULL), width(0), loopDistance(0){
	    initializeConnections();
		setSubTexture(subTexture);
	}
	
	void DefaultLineComponent::setSubTexture(SubTextureInfo * subTexture){
		width = subTexture->size.x;
		loopDistance = subTexture->size.y;
		this->subTexture = subTexture;
	}
	


	DefaultLineComponent::DefaultLineComponent(const DefaultLineComponent &src) : LineComponent() {
	}

	DefaultLineComponent::~DefaultLineComponent() {
	}

	DefaultLineComponent &DefaultLineComponent::operator=(const DefaultLineComponent &src) {
		return *this;
	}

	void DefaultLineComponent::initializeConnections() {
		// We add the connections.
		this->refreshConnections();
		this->addConnection(new ComponentConnection<Mesh>(&this->mesh));
		this->addConnection(new ComponentConnection<Texture>(&this->textureComponent));
	}
	
	void DefaultLineComponent::setVerticesCount(int count){
		mesh->resize(count);
		textureComponent->getTextureCoordinates().resize(count);
	}
	
	void DefaultLineComponent::refreshPoints(){
		if (points.size() < 2) return;
		
		int segmentCount = points.size()-1;
		std::vector<int> subSegmentCount(segmentCount);
		int subSegmentTotal = 0;
		
		for (int i = 0; i < segmentCount; i++) {
			Vector2 p1 = points[i];
			Vector2 p2 = points[i+1];
			Vector2 segment = p2 - p1;
			int currentSegSubSegmentCount = ceilf(segment.getLength() / loopDistance);

			subSegmentTotal += currentSegSubSegmentCount;
			subSegmentCount[i] 	= currentSegSubSegmentCount;
		}
		
		setVerticesCount(subSegmentTotal*4);
		
		int subSegmentIncrement = 0;
		for (int i = 0; i < subSegmentCount.size(); i++) {
			
			int currentSegSubSegmentCount = subSegmentCount[i];
			Vector2 p1 = points[i];
			Vector2 p2 = points[i+1];
			Vector2 segment = p2 - p1;
			Vector2 crossVector;
			crossVector.x = - segment.y;
			crossVector.y = segment.x;
			crossVector.setLength(0.5 * width);

			for (int j = 0; j < currentSegSubSegmentCount; j++) {
				int iterator = (subSegmentIncrement + j);
				int verticesIterator =  iterator * 4;
				Vector2 & v1 = (mesh->getPreTransformVertices()[verticesIterator]);
				Vector2 & v2 = (mesh->getPreTransformVertices()[verticesIterator+1]);
				Vector2 & v3 = (mesh->getPreTransformVertices()[verticesIterator+2]);
				Vector2 & v4 = (mesh->getPreTransformVertices()[verticesIterator+3]);
				
				
				
				Vector2 subSegment = segment;
				float ratio = static_cast<float>(j)/static_cast<float>(currentSegSubSegmentCount);
				subSegment.setLength(segment.getLength() * ratio);
				Vector2 subP1 = p1 + subSegment;
				if(!ratio) subSegment = segment;
				ratio = static_cast<float>(j+1)/static_cast<float>(currentSegSubSegmentCount);
				subSegment.setLength(segment.getLength() * ratio);
				Vector2 subP2 = p1 + subSegment;
				v1 = subP1 + crossVector;
				v2 = subP1 - crossVector;
				v3 = subP2 + crossVector;
				v4 = subP2 - crossVector;
				
//				v1.x += (iterator+0)*150;
//				v2.x += (iterator+0)*150;
//				v3.x += (iterator+0)*150;
//				v4.x += (iterator+0)*150;
				
				(textureComponent->getTextureCoordinates()[verticesIterator]) = subTexture->getTopLeftCoord();
				(textureComponent->getTextureCoordinates()[verticesIterator+1]) = subTexture->getTopRightCoord();
				(textureComponent->getTextureCoordinates()[verticesIterator+2]) = subTexture->getDownLeftCoord();
				(textureComponent->getTextureCoordinates()[verticesIterator+3]) = subTexture->getDownRightCoord();
				float subDiffRatio = (subP2 - subP1).getLength() / loopDistance;
				if(subDiffRatio < 0.95 && j == currentSegSubSegmentCount-1){
					(textureComponent->getTextureCoordinates()[verticesIterator+2]).y *= subDiffRatio;
					(textureComponent->getTextureCoordinates()[verticesIterator+3]).y *= subDiffRatio;
				}
				
				
			}
			subSegmentIncrement += currentSegSubSegmentCount;
		}
	}
	
	void DefaultLineComponent::addPoint(const Vector2 & pos){
		points.push_back(pos);
		refreshPoints();
	}
	
	DefaultLineComponent *DefaultLineComponent::clone() const {
		return new DefaultLineComponent(*this);
	}
	
	
	Vector2 &DefaultLineComponent::getPoint(int index){
		return points[index];
	}


	void DefaultLineComponent::receiveMessage(int senderID, int destID, int message, void *data) {
		this->LineComponent::receiveMessage(senderID, destID, message, data);
	}

	void DefaultLineComponent::update() {
		this->LineComponent::update();
	}
	
	

}
