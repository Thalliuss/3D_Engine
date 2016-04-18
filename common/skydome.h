#ifndef SKYDOME_H
#define SKYDOME_H

#include "common/model.h"

class Skydome: public Model
{
public:
	Skydome();
	virtual ~Skydome();
	void addMesh(const char* o, const char* t);

	bool loadOBJ(
		const char* path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
		);
	void buffers();

	std::vector<glm::vec3> vertices() { return _vertices; }
	std::vector<glm::vec2> uvs() { return _uvs; }
	std::vector<glm::vec3> normals() { return _normals; }

	GLuint texture() { return _texture; }

	GLuint vertexbuffer() { return _vertexbuffer; }
	GLuint uvbuffer() { return _uvbuffer; }
	GLuint normalbuffer() { return _normalbuffer; }


private:
	FILE * file;
	Texture* t;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;

	GLuint _texture;

	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;


	std::string texture_name;
	std::string object_name;
};

#endif // !SKYDOME_H
