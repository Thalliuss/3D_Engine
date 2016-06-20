#include "entity.h"

Entity::Entity()
{
	_texture = "";
	_OBJ = "";

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_lastChild = 0;

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
	for (int i = 0; i < _children.size(); i++) {
		_lastChild = i - 1;
		if (_lastChild > 0 && _children[_lastChild] == e) {
			_children.erase(_children.begin() + i);
		}
	}
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


