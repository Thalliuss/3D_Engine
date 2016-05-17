#include "scene01.h"

// SCENE!
Scene01::Scene01()
{
	skydome = new Skydome();
	this->addChild(skydome);
	skydome->addMesh("assets/skydome.obj", "assets/skydome.DDS");

	cube = new Model();
	this->addChild(cube);
	cube->addMesh("assets/cube.obj", "assets/scene1.DDS");

	sprite = new Sprite();
	cube->addChild(sprite);
	sprite->addTexture("assets/uvmap.DDS");
}

Scene01::~Scene01()
{
	delete skydome;
	delete cube;
	delete sprite;
}

void Scene01::update(float deltaTime) {
	cube->rotation.x += 0.005;
	cube->position.x += 0.005;
}

