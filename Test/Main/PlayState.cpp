#include "PlayState.h"

#include <Core/Entity.h>
#include <Components/Transform.h>

namespace BaconBox {
	PlayState::PlayState(const std::string newName) : State(newName) {
		Entity *entity = new Entity();
		
		Transform *transform = new Transform();
		entity->addComponent(transform);
		
		float f = 30.0f;
		entity->sendMessage(ID<Transform>::NUMBER, Transform::MESSAGE_SET_ROTATION, &f);
		
		float ff = 0.0f;
		entity->sendMessage(ID<Transform>::NUMBER, Transform::MESSAGE_GET_ROTATION, &ff);
		
		std::cout << "omg " << ff << std::endl;
	}
	
	void PlayState::update() {
	}
	
	void PlayState::render() {
	}
}