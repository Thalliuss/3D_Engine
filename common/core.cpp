#include "core.h"

Core::Core()
{
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

	// user clicked the 'close' button in the window
	bool close = false;
	if (glfwGetKey(_renderer.window(), GLFW_KEY_ESCAPE) == GLFW_PRESS &&
		glfwWindowShouldClose(_renderer.window()) == 0) {
		close = true;
	}if (close == true) { scene->stop(); }

}




