#include "scene01.h"

Scene01::Scene01()
{
	s = new Sprite();
	s->position.x = 5;
	this->addSprite(s, "assets/uvmap.DDS");

	cube = new Object();
	cube->position.y = -5;
	this->addObject(cube, "assets/cube.obj", "assets/uvmap.DDS");

	sphere = new Object();
	sphere->position.y = 5;
	sphere->scale.x = 2;
	sphere->scale.y = 2;
	sphere->scale.z = 2;
	this->addObject(sphere, "assets/sphere.obj", "assets/temp.DDS");

	o = new Object();
	this->addObject(o, "assets/cube.obj", "assets/uvmap.DDS");
}


Scene01::~Scene01()
{

}
