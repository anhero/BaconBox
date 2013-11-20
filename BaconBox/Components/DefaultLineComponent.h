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
		DefaultLineComponent(SubTextureInfo * subTexture);

		DefaultLineComponent(const DefaultLineComponent &src);

		void setSubTexture(SubTextureInfo * subTexture);
		virtual ~DefaultLineComponent();
		
		void addPoint(const Vector2 & pos);


		DefaultLineComponent &operator=(const DefaultLineComponent &src);

		DefaultLineComponent *clone() const;
		
		Vector2 &getPoint(int index);


		void receiveMessage(int senderID, int destID, int message, void *data);
		void initializeConnections();
		void refreshPoints();
		void update();
	private:
		void setVerticesCount(int count);
		float loopDistance;
		float width;
		std::vector<Vector2> points;
		Mesh * mesh;
		Texture * textureComponent;
		SubTextureInfo * subTexture;
	};


}

#endif /* defined(BB_DEFAULT_LINECOMPONENT_H) */

