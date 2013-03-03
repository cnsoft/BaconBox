#ifndef BB_DEFAULT_ENTITY_CONTAINER_H
#define BB_DEFAULT_ENTITY_CONTAINER_H

#include <vector>
#include <map>
#include <string>

#include "BaconBox/Components/EntityContainer.h"
#include "BaconBox/Helper/Range.h"

namespace BaconBox {
	class Timeline;
	class EntityContainerLooper;
	
	class DefaultEntityContainer : public EntityContainer {
		friend class EntityContainerLooper;
	public:
		DefaultEntityContainer();
		
		DefaultEntityContainer(const DefaultEntityContainer &src);
		
		virtual ~DefaultEntityContainer();
		
		DefaultEntityContainer &operator=(const DefaultEntityContainer &src);
		
		DefaultEntityContainer *clone() const;
		
		void receiveMessage(int senderID, int destID, int message, void *data);
		
		/**
		 * Updates all the child entities.
		 */
		void update();
		
		/**
		 * Renders all the child entities.
		 */
		void render();
		
		Entity *addChild(Entity *newChild);
		
		Entity *addChildAt(Entity *newChild, int index);
		
		bool contains(Entity *child) const;
		
		Entity *getChildAt(int index);
		
		const Entity *getChildAt(int index) const;
		
		Entity *getChildByName(const std::string &name);
		
		const Entity *getChildByName(const std::string &name) const;
		
		int getChildIndex(Entity *child) const;
		
		std::vector<Entity *> getObjectsUnderPoint(const Vector2 &point);
		
		std::vector<const Entity *> getObjectsUnderPoint(const Vector2 &point) const;
		
		Entity *removeChild(Entity *child);
		
		Entity *removeChildAt(int index);
		
		void removeChildren(int beginIndex, int endIndex);
		
		void setChildIndex(Entity *child, int index);
		
		void swapChildren(Entity *child1, Entity *child2);
		
		void swapChildrenAt(int index1, int index2);
		
		int getNbChildren() const;
	private:
		typedef std::map<Range<int>, Entity *, Range<int>::Comparator> EntityByFrame;
		typedef std::vector<EntityByFrame> ChildArray;
		typedef std::map<std::string, EntityByFrame> ChildMapByName;

		int getCurrentFrameIndex() const;
		
		ChildArray::iterator findChild(Entity *child);
		
		ChildArray::const_iterator findChild(const Entity *child) const;
		
		void initializeConnections();
		
		void updateConnections();
		
		Timeline *timeline;
		
		ChildMapByName childrenByName;
		
		ChildArray children;
	};
}

#endif /* defined(BB_DEFAULT_ENTITY_CONTAINER_H) */

