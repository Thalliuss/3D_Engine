#ifndef SPRITE_H
#define SPRITE_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

#include <common/texture.h>
#include <common/gameobject.h>


class Sprite: public GameObject
{
public:
	Sprite();
	virtual ~Sprite();
	void addTexture(const char* s);
	virtual void update(float deltaTime) {}

	GLuint texture() { return _texture; }
	GLuint vertexbuffer() { return _vertexbuffer; }
	GLuint uvbuffer() { return _uvbuffer; }

private:
	std::string file_name;

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	Texture* t;
};


#endif // !SPRITE_H
