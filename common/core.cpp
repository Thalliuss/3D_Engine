#include "core.h"


Core::Core()
{
	_deltaTime = 0;
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

	scene->updateScene((float) _deltaTime);


	// user clicked the 'close' button in the window
	if (glfwGetKey(_renderer.window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) { scene->stop(); }

	// TODO
	//if (glfwGetKey(_renderer.window(), GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) { scene->next(); }
	// TODO
	//if (glfwGetKey(_renderer.window(), GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) { scene->previous(); }


}




