#include "scene01.h"

Scene01::Scene01()
{
	//sprite = new Sprite();
	//sprite->position.x = 5;
	//sprite->rotation.x = 2;
	//this->addSprite(sprite, "assets/uvmap.DDS");

	cube = new Model();
	//cube->rotation.x = 2;
	this->addModel(cube, "assets/cube.obj", "assets/uvmap.DDS");
}


Scene01::~Scene01()
{

}
