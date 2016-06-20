#include "skybox.h"

Skybox::Skybox()
{
	this->scale -= 3750;
	this->loadOBJ("assets/cube.obj");
	this->isBackground = true;
}

Skybox::~Skybox()
{

}

void Skybox::addTexture(const char* s) {
	_texture = s;
}