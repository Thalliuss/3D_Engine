#include "scene01.h"

Scene01::Scene01()
{
	sprite = new Sprite();
	sprite->position.x = 5;
	this->addSprite(sprite, "assets/uvmap.DDS");

	cube = new Object();
	cube->position.y = -5;
	this->addObject(cube, "assets/cube.obj", "assets/uvmap.DDS");

	cube2 = new Object();
	cube2->position.y = 5;
	cube2->scale.x = 2;
	cube2->scale.y = 2;
	cube2->scale.z = 2;
	this->addObject(cube2, "assets/cube.obj", "assets/uvmap.DDS");

	cube3 = new Object();
	this->addObject(cube3, "assets/cube.obj", "assets/uvmap.DDS");
}


Scene01::~Scene01()
{

}
