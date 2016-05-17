#include "scene02.h"

// SCENE!
Scene02::Scene02()
{
	skydome = new Skydome();
	skydome->addMesh("assets/skydome.obj", "assets/skydome.DDS");
	this->addChild(skydome);

	cube = new Model();
	this->addChild(cube);
	cube->addMesh("assets/cube.OBJ","assets/scene2.DDS");

	sprite = new Sprite();
	this->addChild(sprite);
	sprite->addTexture("assets/uvmap.DDS");

	sprite->position.x = -5;
}

Scene02::~Scene02()
{
	delete skydome;
	delete cube;
	delete sprite;
}

void Scene02::update(float deltaTime) {
	cube->rotation.x += 0.005;
}

