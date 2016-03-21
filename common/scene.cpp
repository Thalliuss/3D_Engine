#include "scene.h"

Scene::Scene()
{
	std::cout << "##### New Scene Initialized  #####\n" << std::endl;
	_camera = new Camera();

	_isRunning = true;

	_sprite = NULL;
	_object = NULL;
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

void Scene::addObject(Object* obj, const char* objstring, const char* ddsstring)
{
	_object = new Object();
	*_object = *obj;
	_object->addMesh(objstring, ddsstring);

	_objectchildren.push_back(_object);
}

