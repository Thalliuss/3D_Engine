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
#include <common/gameobject.h>
#include <common/sprite.h>
#include <common/object.h>

class Scene : public GameObject
{
public:
	Scene();
	~Scene();

	bool isRunning() { return _isRunning; ;}
	void start() { _isRunning = true; }
	void stop() { _isRunning = false; }

	void addSprite(Sprite* spr, const char* ddsstring);	
	void addObject(Object* obj, const char* objstring, const char* ddsstring);

	void updateScene(float deltaTime) {}

	Camera* camera() { return _camera; }

	std::vector<Sprite*> spritechildren() {return _spritechildren;}
	std::vector<Object*> objectchildren() {return _objectchildren;}

private:
	bool _isRunning;

	Camera* _camera;
	Sprite* _sprite;
	Object* _object;

	std::vector<Sprite*> _spritechildren;
	std::vector<Object*> _objectchildren;
};
#endif // SCENE_H