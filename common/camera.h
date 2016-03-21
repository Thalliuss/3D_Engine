#ifndef CAMERA_H
#define CAMERA_H
// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class Camera {
public:
	Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void updateCamera(GLFWwindow* window);
private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::vec3 position;

	float horizontalAngle = 0.0f;
	float verticalAngle = 0.0f;
	float speed = 5.0f; // 5 units / second
	float mouseSpeed = 0.005f;

};


#endif // !CAMERA_H
