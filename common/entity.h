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

#include <vector>

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

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;


	std::string _texture;
	std::string _OBJ;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;

	std::vector<glm::vec3> vertices() { return _vertices; };
	std::vector<glm::vec2> uvs() { return _uvs; }
	std::vector<glm::vec3> normals() { return _normals; };

	std::vector<Entity*> children() { return _children; };


	std::string texture() { return _texture; };
	std::string OBJ() { return _OBJ; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; }
	GLuint normalbuffer() { return _normalbuffer; };

	Texture* t;
	std::vector<std::string> textures;

private:
	std::vector<Entity*> _children;
	int _lastChild;

};
#endif // !ENTITY_H
