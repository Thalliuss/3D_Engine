#include "entity.h"

Entity::Entity()
{
	_texture = NULL;

	position = vec3(0.0f, 0.0f, 0.0f);
	rotation = vec3(0.0f, 0.0f, 0.0f);
	scale = vec3(1.0f, 1.0f, 1.0f);

	isModel = false;
	isSprite = false;
	isBackground = false;
    isChild = false;
	isAlife = false;
}

Entity::~Entity()
{

}

void Entity::addChild(Entity* e) {
	_children.push_back(e); 
	e->isChild = true;
}
void Entity::removeChild(Entity* e) {
	for (int i = 0; i < _children.size(); i++) {
		if (e == _children[i]) {
			_children.erase(_children.begin() + i);
		}
	}
	if (this->isAlife) {
		e->isChild = false;
	}
}

void Entity::update(float deltaTime) {

}

