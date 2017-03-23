#include "scene01.h"

// SCENE!
Scene01::Scene01(){
	sky = new Skybox();
	sky->addTexture("assets/skybox.dds");
	this->addChild(sky);
	
	chunk.create(this, vec3(10, 1, 10));
}

Scene01::~Scene01(){

}

void Scene01::update(float deltaTime) {
}

