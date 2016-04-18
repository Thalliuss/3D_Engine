#include "scene.h"

Scene::Scene()
{
	std::cout << "##### New Scene Initialized  #####\n" << std::endl;
	_camera = new Camera();

	_isRunning = true;

	_sprite = NULL;
	_model = NULL;
	_sky = NULL;
}

Scene::~Scene()
{
	delete _camera;
}

void Scene::addSprite(Sprite* spr)
{
	_spritechildren.push_back(spr);
}

void Scene::addModel(Model* mdl)
{
	_modelchildren.push_back(mdl);
}
void Scene::addBackground(Skydome* mdl) {
	_sky = mdl;
}


void Scene::updateScene(float deltaTime)
{
	//update the Scene
	this->update(deltaTime);

	//update the Background
	if (_sky != NULL) {
		_sky->update(deltaTime);
		_sky->rotation.x += 0.00001;
		_sky->position = _camera->position;
	}
	//update all Models
	for (int i = 0; i < _modelchildren.size(); i++) {
		if (_modelchildren[i] != NULL) {
			_modelchildren[i]->update(deltaTime);

			//###############  Test  ###############
			//_modelchildren[i]->rotation.x += 0.01;
			//######################################
		}
	}
	//update all Sprites
	for (int i = 0; i < _spritechildren.size(); i++) {
		if (_spritechildren[i] != NULL) {
			_spritechildren[i]->update(deltaTime);
		}
	}
}

