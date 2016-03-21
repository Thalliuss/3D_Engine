#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void update(float deltaTime) {}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
private:

};
#endif // !GAMEOBJECT_H
