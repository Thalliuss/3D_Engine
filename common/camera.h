#ifndef CAMERA_H
#define CAMERA_H
// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();

	glm::vec3 position;
	glm::vec2 rotation;

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void updateCamera(GLFWwindow* window);
	virtual void update(float deltaTime) {};

private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;



	float speed = 15.0; // 15 units / second
	float mouseSpeed = 0.0025f;

};


#endif // !CAMERA_H
