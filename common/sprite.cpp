#include "sprite.h"

Sprite::Sprite()
{
	_texture = NULL;
	this->isSprite = true;

	int sprite_width = 5;
	int sprite_height = 5;

	isFirst = true;

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
	GLfloat g_vertex_buffer_data[] = {
		0.5f * sprite_width, -0.5f * sprite_height, 0.0f,
		-0.5f * sprite_width, -0.5f * sprite_height, 0.0f,
		-0.5f * sprite_width,  0.5f * sprite_height, 0.0f,
		-0.5f * sprite_width,  0.5f * sprite_height, 0.0f,
		0.5f * sprite_width,  0.5f * sprite_height, 0.0f,
		0.5f * sprite_width, -0.5f * sprite_height, 0.0f
	};

	// Two UV coordinates for each vertex.
	GLfloat g_uv_buffer_data[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	//TODO
	//glGenBuffers(1, &_normalbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data), g_normal_buffer_data, GL_STATIC_DRAW);
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
	glDeleteBuffers(1, &_normalbuffer);
}

void Sprite::addTexture(const char* string) {
	if (string != NULL && string != _lastDDS) {
		if (isFirst) {
			std::cout << "#####  New Sprite Created  #####" << std::endl;
			std::cout << "Initializing Sprite's Texture Using:" << std::endl;
			printf("DDS file %s\n", string);
			std::cout << "Sprite's Texture Succesfully Initialized..." << std::endl;
			std::cout << "\n" << std::endl;
			isFirst = false;
		}
		_texture = t->loadDDS(string);
	}
	_lastDDS = string;
}




