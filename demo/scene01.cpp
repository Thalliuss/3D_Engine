#include "scene01.h"

Scene01::Scene01()
{

	sprite = new Sprite();
	sprite->addTexture("assets/uvmap.DDS");
	this->addSprite(sprite);

	sprite->position.x = 5;

	cube = new Model();
	cube->addMesh("assets/dat muntje van kevin.obj", "assets/coin-texture.DDS");
	this->addModel(cube);

	cube->position.x = 20;
	cube->rotation.y = 1.55;


	skydome = new Skydome();
	skydome->addMesh("assets/skydome.obj", "assets/skydome.DDS");
	this->addBackground(skydome);

	skydome->position.y = -20;
}

Scene01::~Scene01()
{

}
void Scene01::update(float deltaTime) {
	cube->rotation.x += 0.005;
	sprite->position.y += 0.0005;
}