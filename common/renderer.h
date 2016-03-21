#ifndef RENDERER_H
#define RENDERER_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
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

#include <common/camera.h>
#include <common/sprite.h>
#include <common/object.h>
#include <common/shader.h>
#include <common/scene.h>
#include <vector>

class Renderer 
{
public:
	Renderer();
	virtual ~Renderer();
	void renderScene(Scene* scene);
	void renderSprite(Sprite* sprite);
	void renderObject(Object* object);

	GLFWwindow* window() { return _window; };

private:
	int init();
	GLFWwindow* _window;
	int window_width;
	int window_height;

	std::string fragment_shader;
	std::string vertex_shader;

	GLuint vertexPosition_modelspaceID;
	GLuint vertexUVID;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	GLuint programID;
	GLuint matrixID;
	GLuint textureID;

	Shader* shader;
};


#endif // !RENDERER_H
