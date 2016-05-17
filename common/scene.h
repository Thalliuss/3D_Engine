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
#include <common/skydome.h>

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

	void addChild(Entity* e);
	void removeChild(Entity* e);

	void updateScene(float deltaTime);

	void updateChildren(float deltaTime, Entity* child, Entity* parent, vec3 offset);

	Camera* camera() { return _camera; }

	std::vector<Entity*> children() { return _children; }

private:
	bool _isRunning;

	int _lastChild;

	Camera* _camera;

	std::vector<Entity*> _children;

};
#endif // SCENE_H