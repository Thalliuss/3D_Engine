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

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <common/texture.h>
#include <common/entity.h>

class Sprite: public Entity
{
public:
	Sprite();
	virtual ~Sprite();
	void addTexture(const char* s);
	virtual void update(float deltaTime) {}

	GLuint texture() { return _texture; }
	GLuint vertexbuffer() { return _vertexbuffer; }
	GLuint uvbuffer() { return _uvbuffer; }
	GLuint normalbuffer() { return _normalbuffer; }


private:
	std::string file_name;

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;


	Texture* t;
};


#endif // !SPRITE_H
