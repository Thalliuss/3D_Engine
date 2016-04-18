#include "entity.h"

Entity::Entity()
{
	position = vec3(0.0f, 0.0f, 0.0f);
	rotation = vec3(0.0f, 0.0f, 0.0f);
	scale = vec3(1.0f, 1.0f, 1.0f);
}

Entity::~Entity()
{

}

void Entity::update(float deltaTime) {

}

