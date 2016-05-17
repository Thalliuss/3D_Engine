#include "scene.h"

Scene::Scene()
{
	std::cout << "##### New Scene Initialized  #####\n" << std::endl;
	_camera = new Camera();

	_isRunning = true;
	_lastChild = NULL;
}

Scene::~Scene()
{
	delete _camera;
}

void Scene::addChild(Entity* e) {
	if (!e->isChild) {
		_children.push_back(e);
		for (int i = 0; i < _children.size(); i++) {
			_lastChild = i - 1;
			if (_lastChild > 0 && _children[_lastChild] == e) {
				_children.erase(_children.begin() + i);
			}
		}
	}
	e->isAlife = true;
}

void Scene::removeChild(Entity* e) {
	for (int i = 0; i < _children.size(); i++) {
		if (e == _children[i]) {
			_children.erase(_children.begin() + i);
			for (int o = 0; o < _children[i]->children().size(); o++) {
				_children.erase(_children[i]->children().begin() + i);
				_children[i]->children()[o]->isChild = true;
			}
		}
	}
	e->isAlife = false;
}

void Scene::updateChildren(float deltaTime, Entity* child, Entity* parent, vec3 offset) { //TODO Implement
	child->rotation = parent->rotation;
	child->position = parent->position;
}

void Scene::updateScene(float deltaTime)
{
	//update the Scene
	this->update(deltaTime);
	//update all Entity's
	for (int i = 0; i < _children.size(); i++) {
		if (_children[i] != NULL) {
			_children[i]->update(deltaTime);
		}
		//lock skydome position to the camera
		if (_children[i]->isBackground) {
			_children[i]->position = camera()->position;
		}
		for (int o = 0; o < _children[i]->children().size(); o++) {
			vec3 offset = _children[i]->children()[o]->position;
			//update all entity's children
			_children[i]->children()[o]->update(deltaTime);
			updateChildren(deltaTime, _children[i]->children()[o], _children[i], offset);
		}
	}
	//update the Camara
	if (_camera != NULL) {
		_camera->update(deltaTime);
	}
}

