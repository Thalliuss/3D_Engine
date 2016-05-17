#ifndef ENTITY_H
#define ENTITY_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <vector>
using namespace std;

#include "common/camera.h"
#include "common/texture.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void update(float deltaTime);

	void Entity::addChild(Entity* e);
	void Entity::removeChild(Entity* e);

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	bool isModel;
	bool isSprite;
	bool isBackground;
	bool isChild;
	bool isAlife;

	vector<vec3> _vertices;
	vector<vec2> _uvs;
	vector<vec3> _normals;

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;

	vector<vec3> vertices() { return _vertices; }
	vector<vec2> uvs() { return _uvs; }
	vector<vec3> normals() { return _normals; }

	vector<Entity*> children() { return _children; }


	GLuint texture() { return _texture; }
	GLuint vertexbuffer() { return _vertexbuffer; }
	GLuint uvbuffer() { return _uvbuffer; }
	GLuint normalbuffer() { return _normalbuffer; }

	Texture* t;

private:
	vector<Entity*> _children;
};
#endif // !ENTITY_H
