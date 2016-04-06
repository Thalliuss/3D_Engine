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


