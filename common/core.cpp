#include "core.h"


Core::Core()
{
	_deltaTime = 0;
	counter = 0;
}


Core::~Core()
{
}

void Core::run(Scene* scene)
{
	// Render Scene
	_renderer.renderScene(scene);

	// Update camera instance in Scene
	scene->camera()->updateCamera(_renderer.window());

	// Call the update method every frame
	scene->updateScene((float) _deltaTime);

	// User pressed the 'close' button
	if (glfwGetKey(_renderer.window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) { scene->stop(); }

	// Next Scene
	if (glfwGetKey(_renderer.window(), GLFW_KEY_P) == GLFW_PRESS) { if (counter < scenes.size() - 1) { counter++; } }

	// Previous Scene
	if (glfwGetKey(_renderer.window(), GLFW_KEY_O) == GLFW_PRESS) { if (counter > 0) { counter--; } }
}




