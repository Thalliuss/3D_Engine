#include "scene01.h"

Scene01::Scene01()
{

	sprite = new Sprite();
	sprite->position.x = 5;
	//sprite->rotation.x = 2;
	this->addSprite(sprite, "assets/uvmap.DDS");

	cube = new Model();
	cube->position.y = -20;
	cube->scale.x = 2.7;
	cube->scale.y = 2.7;
	cube->scale.z = 2.7;
	this->addModel(cube, "assets/mh03.obj", "assets/uvmap.DDS");

	skydome = new Skydome();
	skydome->position.y = -20;
	this->addModel(skydome, "assets/skydome.obj", "assets/skydome.DDS");

}

Scene01::~Scene01()
{

}
