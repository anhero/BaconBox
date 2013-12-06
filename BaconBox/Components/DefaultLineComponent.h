#ifndef BB_DEFAULT_LINECOMPONENT_H
#define BB_DEFAULT_LINECOMPONENT_H

#include "BaconBox/Components/LineComponent.h"



namespace BaconBox {
	class Mesh;
	class Texture;
	class SubTextureInfo
;
	class DefaultLineComponent : public LineComponent {
	public:
		DefaultLineComponent(SubTextureInfo * subTexture, bool inversedSubTex = false);

		DefaultLineComponent(const DefaultLineComponent &src);
		void setPatternSpacing(float patternSpacing);
		void setTextureHeadStart(float textureHeadStart);
		void setSegmentHeadStart(float segmentHeadStart);
		int getPointCount();
		void addPoint(const Vector2 & pos);
		void setSubTexture(SubTextureInfo * subTexture, bool inversedSubTex = false);
		virtual ~DefaultLineComponent();

		DefaultLineComponent &operator=(const DefaultLineComponent &src);

		DefaultLineComponent *clone() const;
		
		Vector2 &getPoint(int index);
		float getTextureHeadStartAt(int index);
//		float getSegmentHeadStartAt(int index);
		void receiveMessage(int senderID, int destID, int message, void *data);
		void initializeConnections();
		void refreshPoints();
		void update();
	private:
		void setVerticesCount(int count);
		float loopDistance;
		float textureCoordLoopDistance;
		float patternSpacing;
		float width;
		std::vector<Vector2> points;
//		std::deque<float> segmentHeadStarts;
		std::deque<float> textureHeadStarts;
		Mesh * mesh;
		Texture * textureComponent;
		SubTextureInfo * subTexture;
		bool inversedSubTex;
		float textureHeadStart;
//		float segmentHeadStart;
	};


}

#endif /* defined(BB_DEFAULT_LINECOMPONENT_H) */

