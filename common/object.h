#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

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

#include <vector>
#include <common/texture.h>
#include <common/gameobject.h>

class Object: public GameObject
{
public:
	Object();
	virtual ~Object();

	void Object::addMesh(const char* o, const char* t);

	bool loadOBJ(
		const char* path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
	);
	void buffers();

	std::vector<glm::vec3> vertices() { return _vertices; }
	std::vector<glm::vec2> uvs() { return _uvs; }
	//currently unused.
	std::vector<glm::vec3> normals() { return _normals; }

	GLuint vertexbuffer() { return _vertexbuffer; }
	GLuint texture() { return _texture; }
	GLuint uvbuffer() { return _uvbuffer; }

private:
	FILE * file;
	Texture* t;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;

	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _texture;

	std::string texture_name;
	std::string object_name;

};

#endif // !OBJECTLOADER_H

