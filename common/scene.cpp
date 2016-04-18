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

void Scene::addSprite(Sprite* spr, const char* ddsstring)
{
	_sprite = new Sprite();
	*_sprite = *spr;
	_sprite->addTexture(ddsstring);

	_spritechildren.push_back(_sprite);
}

void Scene::addModel(Model* mdl, const char* objstring, const char* ddsstring)
{
	_model = new Model();
	*_model = *mdl;
	_model->addMesh(objstring, ddsstring);

	_modelchildren.push_back(_model);
}
void Scene::addBackground(Skydome* mdl, const char* objstring, const char* ddsstring) {
	_sky = new Skydome();
	*_sky = *mdl;
	_sky->addMesh(objstring, ddsstring);
}

void Scene::updateScene(float deltaTime)
{
	this->update(deltaTime);
	if (_sky != NULL) {
		_sky->update(deltaTime);
		_sky->rotation.x += 0.00001;
		_sky->position = _camera->position;
	}
	for (int i = 0; i < _modelchildren.size(); i++) {
		if (_modelchildren[i] != NULL) {
			Model* _m = new Model();
			_m = _modelchildren[i];
			if (_m != NULL) {
				_m->update(deltaTime);

				//--==[ Test ]==---
				_m->rotation.x += 0.01;
				_m->scale.x += 0.001;
				_m->scale.y += 0.001;
				_m->scale.z += 0.001;
			}
		}
	}
}

