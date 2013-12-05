#include "DefaultLineComponent.h"
#include "BaconBox/Console.h"

#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/Display/SubTextureInfo.h"

#include <algorithm>
#include <utility> 
#include <deque>
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
		
		
		Vector2 untouchedTC1 = (inversedSubTex ? subTexture->getTopLeftCoord()   : subTexture->getTopLeftCoord()  );
		Vector2 untouchedTC2 = (inversedSubTex ? subTexture->getDownLeftCoord()  : subTexture->getTopRightCoord() );
		Vector2 untouchedTC3 = (inversedSubTex ? subTexture->getTopRightCoord()  : subTexture->getDownLeftCoord() );
		Vector2 untouchedTC4 = (inversedSubTex ? subTexture->getDownRightCoord() : subTexture->getDownRightCoord());
		
		float textureHeadStart = 0.0f;
		float segmentHeadStart = 0.0f;
		
		std::deque<std::pair<Vector2, Vector2> > tempMesh;
		Vector2 nextStartCrossVector;
		int verticesIterator = 0;

		for (int i = 0; i < segmentCount; i++) {
			bool isLastSegment = i == segmentCount -1;
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
			
			bool subSegmentInProgress = true;
			Vector2 subP1;
			Vector2 subP2;
			bool firstSubSegment = true;
			while (subSegmentInProgress) {
			
				float tempTextureHeadStart = textureHeadStart;
				tempMesh.resize(verticesIterator+4);

				std::pair<Vector2, Vector2> & pair1 = tempMesh[verticesIterator];
				std::pair<Vector2, Vector2> & pair2 = tempMesh[verticesIterator+1];
				std::pair<Vector2, Vector2> & pair3 = tempMesh[verticesIterator+2];
				std::pair<Vector2, Vector2> & pair4 = tempMesh[verticesIterator+3];
				Vector2 & v1 = tempMesh[verticesIterator].first;
				Vector2 & v2 = tempMesh[verticesIterator+1].first;
				Vector2 & v3 = tempMesh[verticesIterator+2].first;
				Vector2 & v4 = tempMesh[verticesIterator+3].first;
				Vector2 & tc1 = tempMesh[verticesIterator].second;
				Vector2 & tc2 = tempMesh[verticesIterator+1].second;
				Vector2 & tc3 = tempMesh[verticesIterator+2].second;
				Vector2 & tc4 = tempMesh[verticesIterator+3].second;
				verticesIterator += 4;
				
				subP1 = segment;
				subP1.setLength(segmentLenght - remnantSegmentLenght);
				
				bool endPattern = true;
				bool clearSpacing = true;
				float subSegmentLenght;
				bool clearTextureHeadStart = false;
				float loopWithSpacing = loopDistance + patternSpacing;
				if (remnantSegmentLenght < loopWithSpacing -textureHeadStart) {
					clearSpacing = false;
					subSegmentInProgress = false;
					
					if (remnantSegmentLenght < loopDistance) {
						endPattern = false;
						subSegmentLenght = remnantSegmentLenght;
						textureHeadStart = remnantSegmentLenght +textureHeadStart;
						segmentHeadStart = 0;
						
					}
					else{
						subSegmentLenght = loopDistance;
						segmentHeadStart = loopWithSpacing - remnantSegmentLenght;
						textureHeadStart = 0;
					}
				}
				else{
					subSegmentLenght = loopDistance - textureHeadStart;
					segmentHeadStart = 0;
					remnantSegmentLenght -= subSegmentLenght + patternSpacing;
					clearTextureHeadStart = true;
				}
				
				Vector2 subSegment = segment;
				subSegment.setLength(subSegmentLenght);
				
				
				subP1+=p1;
				subP2 = subP1 + subSegment;
				
				Vector2 crossVector1(middleCrossVector);
				Vector2 crossVector2(middleCrossVector);
				if (!isLastSegment && !subSegmentInProgress) {
					crossVector2 = endCrossVector;
				}
				if (firstSubSegment){
					crossVector1 = startCrossVector;
				}
//

				
				v1 = subP1 + crossVector1;
				v2 = subP1 - crossVector1;
				v3 = subP2 + crossVector2;
				v4 = subP2 - crossVector2;
				
				tc1 = untouchedTC1;
				tc2 = untouchedTC2;
				tc3 = untouchedTC3;
				tc4 = untouchedTC4;
				
				float loopDistanceRatio = (textureCoordLoopDistance/loopDistance);

				Vector2 headStartTC(untouchedTC3 - untouchedTC1);
				Vector2 overTC(headStartTC);

				if (tempTextureHeadStart > 0) {
					headStartTC.setLength(tempTextureHeadStart * loopDistanceRatio);
					
					tc1 += headStartTC;
					tc2 += headStartTC;
				}
				
				tc3 = untouchedTC3;
				tc4 = untouchedTC4;
				
				if (!endPattern) {
					float overTCLenght = loopDistance - subSegmentLenght - tempTextureHeadStart;
					overTC.setLength(overTCLenght * loopDistanceRatio);
					tc3 -= overTC;
					tc4 -= overTC;
				}
				
				if(clearTextureHeadStart) textureHeadStart = 0;
				
				firstSubSegment = false;

			}

		}
		
		int tempMeshSize = tempMesh.size();
		setVerticesCount(tempMeshSize);
		
		for (int i = 0; i < tempMeshSize; i++) {
			std::pair<Vector2, Vector2> & pair = tempMesh[i];
			mesh->getPreTransformVertices()[i] = pair.first;
			textureComponent->getTextureCoordinates()[i] = pair.second;
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
