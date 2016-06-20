#ifndef MESH_H
#define MESH_H

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

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();
	bool loadOBJ(const char* path);

	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; }
	GLuint normalbuffer() { return _normalbuffer; };

	std::vector<glm::vec3> vertices() { return _vertices; };
	std::vector<glm::vec2> uvs() { return _uvs; }
	std::vector<glm::vec3> normals() { return _normals; };
private:
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
};

#endif // !MESH_H

