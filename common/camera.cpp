#include <common/camera.h>

Camera::Camera() {
	ProjectionMatrix = perspective(45.0f, 16.0f / 9.0f, 0.1f, 3300.0f);
	position = vec3(0, 0, -5);
	rotation = vec2(0, 0);
}

mat4 Camera::getViewMatrix() {
	return ViewMatrix;
}
mat4 Camera::getProjectionMatrix() {
	return ProjectionMatrix;
}

// called from Core::run(Scene* scene)
void Camera::updateCamera(GLFWwindow* window)
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1920 / 2, 1080 / 2);

	// Compute new orientation
	rotation.x += mouseSpeed * float(1920 / 2 - xpos);
	rotation.y += mouseSpeed * float(1080 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	vec3 direction(
		cos(rotation.y) * sin(rotation.x),
		sin(rotation.y),
		cos(rotation.y) * cos(rotation.x)
		);

	// Right vector
	vec3 right = vec3(
		sin(rotation.x - 3.14f / 2.0f),
		0,
		cos(rotation.x - 3.14f / 2.0f)
		);
	// Up vector
	vec3 up = cross(right, direction);
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}

	// Camera matrix
	ViewMatrix = lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

}