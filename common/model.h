#ifndef MODEL_H
#define MODEL_H

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
#include <common/texture.h>
#include <common/entity.h>
using namespace std;


class Model: public Entity
{
public:
	Model();
	virtual ~Model();

	void addMesh(const char* o, const char* t);

	bool loadOBJ(
		const char* path,
		vector<vec3> & out_vertices,
		vector<vec2> & out_uvs,
		vector<vec3> & out_normals
	);
	void buffers();

	vector<vec3> vertices() { return _vertices; }
	vector<vec2> uvs() { return _uvs; }
	vector<vec3> normals() { return _normals; }

	GLuint texture() { return _texture; }

	GLuint vertexbuffer() { return _vertexbuffer; }
	GLuint uvbuffer() { return _uvbuffer; }
	GLuint normalbuffer() { return _normalbuffer; }

private:
	FILE * file;
	Texture* t;

	vector<vec3> _vertices;
	vector<vec2> _uvs;
	vector<vec3> _normals;

	GLuint _texture;

	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;


	string texture_name;
	string object_name;

};

#endif // !MODEL_H

