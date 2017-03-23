#include "skybox.h"

Skybox::Skybox()
{
	this->scale = glm::vec3(-100, -100, -100);
	this->loadOBJ("assets/cube.obj");
	this->isBackground = true;
}

Skybox::~Skybox()
{

}

void Skybox::addTexture(const char* s) {
	_texture = s;
}