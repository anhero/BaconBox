#include "DefaultLineComponent.h"
#include "BaconBox/Console.h"

#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/Display/SubTextureInfo.h"

#include <algorithm>


namespace BaconBox {
	DefaultLineComponent::DefaultLineComponent(SubTextureInfo * subTexture, bool inversedSubTex) : LineComponent(),  mesh(NULL), width(0), loopDistance(0), textureCoordLoopDistance(0), patternSpacing(0.0f){
	    initializeConnections();
		this->setSubTexture(subTexture, inversedSubTex);
	}
	
	void DefaultLineComponent::setSubTexture(SubTextureInfo * subTexture, bool inversedSubTex){
		width = (inversedSubTex ? subTexture->size.y : subTexture->size.x);
		loopDistance = (inversedSubTex ? subTexture->size.x : subTexture->size.y);
		textureCoordLoopDistance = (inversedSubTex ? subTexture->getTextureCoordinateSize().x : subTexture->getTextureCoordinateSize().y);

		this->subTexture = subTexture;
		this->inversedSubTex = inversedSubTex;
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
	void DefaultLineComponent::setPatternSpacing(float patternSpacing){
		this->patternSpacing = patternSpacing;
	}

	void DefaultLineComponent::refreshPoints(){
		if (points.size() < 2) return;
		
		int segmentCount = points.size()-1;
		std::vector<int> subSegmentCount(segmentCount);
		int subSegmentTotal = 0;
		float segmentHeadStart = 0.0f;
		for (int i = 0; i < segmentCount; i++) {
			Vector2 p1 = points[i];
			Vector2 p2 = points[i+1];
			Vector2 segment = p2 - p1;
			float segmentLenght = segment.getLength();
			int currentSegSubSegmentCount = ceilf((segmentLenght+segmentHeadStart) / loopDistance);
			segmentHeadStart = std::abs(loopDistance - (((currentSegSubSegmentCount * loopDistance - segmentHeadStart) - segmentLenght)));
			subSegmentTotal += currentSegSubSegmentCount;
			subSegmentCount[i] 	= currentSegSubSegmentCount;
		}
		
		setVerticesCount(subSegmentTotal*4);
		
		int subSegmentIncrement = 0;
		
		
		Vector2 unctouchedTC1 = (inversedSubTex ? subTexture->getTopLeftCoord()   : subTexture->getTopLeftCoord()  );
		Vector2 unctouchedTC2 = (inversedSubTex ? subTexture->getDownLeftCoord()  : subTexture->getTopRightCoord() );
		Vector2 unctouchedTC3 = (inversedSubTex ? subTexture->getTopRightCoord()  : subTexture->getDownLeftCoord() );
		Vector2 unctouchedTC4 = (inversedSubTex ? subTexture->getDownRightCoord() : subTexture->getDownRightCoord());
		
		segmentHeadStart = 0.0f;
		
		Vector2 nextStartCrossVector;
		
		for (int i = 0; i < segmentCount; i++) {
			bool isLastSegment = i == segmentCount -1;
			int currentSegSubSegmentCount = subSegmentCount[i];
			const Vector2 p1 = points[i];
			const Vector2 p2 = points[i+1];
			const Vector2 segment = p2 - p1;
			const float segmentLenght = segment.getLength();
			float remnantSegmentLenght = segmentLenght;

			
			Vector2 startCrossVector;
			Vector2 endCrossVector;
			Vector2 middleCrossVector;
			
			middleCrossVector.x = - segment.y;
			middleCrossVector.y = segment.x;
			middleCrossVector.setLength(0.5 * width);
			
			if (i == 0) {
				startCrossVector = middleCrossVector;
			}
			else{
				startCrossVector = nextStartCrossVector;
			}
			
			if (isLastSegment) {
				endCrossVector.x = - segment.y;
				endCrossVector.y = segment.x;
				endCrossVector.setLength(0.5 * width);
			}
			else {
				endCrossVector  = points[i+2] - p1;
				float temp = endCrossVector.x;
				endCrossVector.x = -endCrossVector.y;
				endCrossVector.y = temp;
			}
			startCrossVector.setLength(0.5 * width);
			endCrossVector.setLength(0.5 * width);
			nextStartCrossVector = endCrossVector;

			
			for (int j = 0; j < currentSegSubSegmentCount; j++) {
				bool isLastSubSegment = j == currentSegSubSegmentCount-1;

				int iterator = (subSegmentIncrement + j);
				int verticesIterator =  iterator * 4;
				
				//Position
				Vector2 & v1 = (mesh->getPreTransformVertices()[verticesIterator]);
				Vector2 & v2 = (mesh->getPreTransformVertices()[verticesIterator+1]);
				Vector2 & v3 = (mesh->getPreTransformVertices()[verticesIterator+2]);
				Vector2 & v4 = (mesh->getPreTransformVertices()[verticesIterator+3]);

				

				
				Vector2 subSegment = segment;
				float subSegmentLenght = loopDistance;
				if (j == 0) {
					subSegmentLenght -= segmentHeadStart;
				}
				subSegmentLenght = std::min(remnantSegmentLenght, subSegmentLenght);
				subSegment.setLength(subSegmentLenght);
				
				Vector2 subP1 = segment;
				subP1.setLength(segmentLenght - remnantSegmentLenght  );
				subP1 += p1;
				Vector2 subP2 = subP1 + subSegment;
				
				Vector2 crossVector1(middleCrossVector);
				Vector2 crossVector2(middleCrossVector);
				if (!isLastSegment && isLastSubSegment) {
					crossVector2 = endCrossVector;
				}
				if (j == 0){
					crossVector1 = startCrossVector;
				}
				v1 = subP1 + crossVector1;
				v2 = subP1 - crossVector1;
				v3 = subP2 + crossVector2;
				v4 = subP2 - crossVector2;
				
				remnantSegmentLenght -= subSegmentLenght;
				
				//Texture coordinate
				Vector2 & tc1 = (textureComponent->getTextureCoordinates()[verticesIterator]);
				Vector2 & tc2 = (textureComponent->getTextureCoordinates()[verticesIterator+1]);
				Vector2 & tc3 = (textureComponent->getTextureCoordinates()[verticesIterator+2]);
				Vector2 & tc4 = (textureComponent->getTextureCoordinates()[verticesIterator+3]);
				
				float loopDistanceRatio = (textureCoordLoopDistance/loopDistance);
//				float subSegmentLenghtTC = subSegmentLenght * loopDistanceRatio;
//				float segmentHeadStartTC = segmentHeadStart * loopDistanceRatio;

				Vector2 headStartTC = unctouchedTC3 - unctouchedTC1;
				Vector2 overTC = headStartTC;
				
				tc1 = unctouchedTC1;
				tc2 = unctouchedTC2;
				if (j==0) {
					headStartTC.setLength(segmentHeadStart * loopDistanceRatio);

					tc1 += headStartTC;
					tc2 += headStartTC;
				}
				tc3 = unctouchedTC3;
				tc4 = unctouchedTC4;
				if (isLastSubSegment) {
//					overTC.setLength(loopDistanceRatio * ((loopDistance *subSegmentCount - segmentHeadStart) - subSegmentLenght));
					float overTCLenght = (((loopDistance * currentSegSubSegmentCount) - segmentHeadStart) - segmentLenght);
					overTC.setLength(overTCLenght * loopDistanceRatio);
					tc3 -= overTC;
					tc4 -= overTC;
				}

				
				
				
				if (isLastSubSegment) {
					if (j != 0) {
						segmentHeadStart = 0;
					}
					segmentHeadStart += subSegmentLenght;
					
				}
				
			}
			subSegmentIncrement += currentSegSubSegmentCount;
		}
	}
	
	void DefaultLineComponent::addPoint(const Vector2 & pos){
		points.push_back(pos);
//		refreshPoints();
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
