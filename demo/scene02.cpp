#include "scene02.h"

// SCENE!
Scene02::Scene02()
{
	sky = new Skybox();
	sky->addTexture("assets/uvmap.dds");
	this->addChild(sky);

	cube = new Model();
	this->addChild(cube);
	cube->addMesh("assets/cube.OBJ","assets/uvmap.DDS");

	sprite = new Sprite();
	this->addChild(sprite);
	sprite->addTexture("assets/uvmap.DDS");

	sprite->position.x = -5;
	cube->position.x = 15;
}

Scene02::~Scene02()
{
	delete sky;
	delete cube;
	delete sprite;
}

void Scene02::update(float deltaTime) {
	sprite->rotation.x += 0.005;
	if (camera()->position.x <= cube->position.x + 2 && camera()->position.x >= cube->position.x + -2
		&& camera()->position.y <= cube->position.y + 2 && camera()->position.y >= cube->position.y + -2
		&& camera()->position.z <= cube->position.z + 2 && camera()->position.z >= cube->position.z + -2) {
		std::cout << "LOL WERKT" << std::endl;
	}
}

