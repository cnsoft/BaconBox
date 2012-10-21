#ifndef BB_ENTITY_H
#define BB_ENTITY_H

#include <vector>
#include <string>

namespace BaconBox {
	class Component;
	
	/**
	 * Represents an entity that has components and can contain other entities.
	 */
	class Entity {
	public:
		void sendMessage(int id, int message, void *data);
		
		const std::string &getName() const;
		void setName(const std::string &newName);
		
		const std::vector<Component *> &getComponents() const;
		void addComponent(Component *newComponent);
		void removeComponentAt(std::vector<Component *>::size_type index);
		void removeComponent(Component *component);
		void removeComponents(int id);

		const std::vector<Entity *> &getChildren() const;
		void addChild(Entity *newChild);
		void removeChildAt(std::vector<Entity *>::size_type index);
		void removeChild(Entity *child);
	private:
		std::string name;
		std::vector<Component *> components;
		std::vector<Entity *> children;
		Entity *parent;
	};
}

#endif
