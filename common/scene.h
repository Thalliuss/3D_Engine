#ifndef SCENE_H
#define SCENE_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

#include <vector>
#include <common/camera.h>
#include <common/entity.h>

#include <common/sprite.h>
#include <common/model.h>

class Scene : public Entity
{
public:
	Scene();
	~Scene();

	bool isRunning() { return _isRunning; ;}
	void start() { _isRunning = true; }
	void stop() { _isRunning = false; }

	void addSprite(Sprite* spr, const char* ddsstring);	
	void addModel(Model* mdl, const char* objstring, const char* ddsstring);

	void updateScene(float deltaTime) {}

	Camera* camera() { return _camera; }

	std::vector<Sprite*> spritechildren() {return _spritechildren;}
	std::vector<Model*> modelchildren() {return _modelchildren;}

private:
	bool _isRunning;

	Camera* _camera;
	Sprite* _sprite;
	Model* _model;

	std::vector<Sprite*> _spritechildren;
	std::vector<Model*> _modelchildren;
};
#endif // SCENE_H