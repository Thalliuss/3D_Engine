#include "renderer.h"

Renderer::Renderer()
{
	window_width = 1024;
	window_height = 768;

	fragment_shader = "shaders/sprite.frag";
	vertex_shader = "shaders/sprite.vert";

	this->init();
}

Renderer::~Renderer()
{
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
}

int Renderer::init() 
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);	

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow(window_width, window_height, "Demo", NULL, NULL);
	if (_window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	
// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(_window, 1024 / 2, 768 / 2);

	// background
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	// see: shader.h/cpp
	programID = shader->LoadShaders(vertex_shader.c_str(), fragment_shader.c_str());

	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexUVID = glGetAttribLocation(programID, "vertexUV");

	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");
	// Get a handle for our "myTextureSampler" uniform
	textureID = glGetUniformLocation(programID, "myTextureSampler");

	ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	return 0;
}

void Renderer::renderScene(Scene* scene)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get viewMatrix from Camera (Camera position and direction)
	ViewMatrix = scene->camera()->getViewMatrix();

	// see if we need to render anything
	std::vector<Model*> models = scene->modelchildren();
	for (int i = 0; i < models.size(); i++) {
		Model* model = new Model();
		model = models[i];
		if (model != NULL) {
			// render the Object 
			this->renderModel(model);
		}
	}
	std::vector<Sprite*> sprites = scene->spritechildren();
	for (int i = 0; i < sprites.size(); i++) {
		Sprite* sprite = new Sprite;
		sprite = sprites[i];
		if (sprite != NULL) {
			// render the Sprite 
			this->renderSprite(sprite);
		}
	}

	// Swap buffers
	glfwSwapBuffers(_window);
	glfwPollEvents();
}


void Renderer::renderSprite(Sprite* s)
{
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	// Use our shader
	glUseProgram(programID);

	// Build the Model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(s->position.x, s->position.y, s->position.z));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(s->rotation.x, s->rotation.y, s->rotation.z);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(s->scale.x, s->scale.y, s->scale.z));

	ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, s->texture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, s->vertexbuffer());
	glVertexAttribPointer(
		vertexPosition_modelspaceID,  // The attribute we want to configure
		3,							// size : x+y+z => 3
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, s->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,				   // The attribute we want to configure
		2,							// size : U+V => 2
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
}
void Renderer::renderModel(Model* m)
{
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	// Use our shader
	glUseProgram(programID);

	// Build the Model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m->position.x, m->position.y, m->position.z));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(m->rotation.x, m->rotation.y, m->rotation.z);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m->scale.x, m->scale.y, m->scale.z));

	ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	if (m->texture() != NULL) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m->texture());
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(textureID, 0);
	}

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, m->vertexbuffer());
	glVertexAttribPointer(
		vertexPosition_modelspaceID,  // The attribute we want to configure
		3,							// size : x+y+z => 3
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, m->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,				   // The attribute we want to configure
		2,							// size : U+V => 2
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
		);


	glDrawArrays(GL_TRIANGLES, 0, m->vertices().size());

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
}



