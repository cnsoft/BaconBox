#ifndef BB_LINECOMPONENT_H
#define BB_LINECOMPONENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Vector2.h"
namespace BaconBox {
	/**
	 * Base class for components that manage the animations and its frames.
	 */
	class LineComponent : public Component {
	public:
		BB_ID_HEADER;


		LineComponent();

		LineComponent(const LineComponent &src);
		virtual void addPoint(const Vector2 & point) = 0;
		virtual void setPatternSpacing(float patternSpacing) = 0;
		virtual void refreshPoints() = 0;
		virtual ~LineComponent();
		virtual Vector2 &getPoint(int index) = 0;
		virtual void receiveMessage(int senderID, int destID, int message, void *data);

	};


	class LineComponentProxy : public ComponentProxy {
	public:
		LineComponentProxy(Entity *entity);
		void addPoint(const Vector2 & point);
		Vector2 &getPoint(int index);
		void setPatternSpacing(float patternSpacing);

		void refreshPoints();
	protected:
	    void setLineComponent(LineComponent * lineComponent);
	};
}

#endif /* defined(BB_LINECOMPONENT_H) */

