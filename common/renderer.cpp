#include "renderer.h"

Renderer::Renderer()
{
	window_width = 1024;
	window_height = 750;

	fullbright_fragment_shader = "shaders/fullbright.frag";
	fullbright_vertex_shader = "shaders/fullbright.vert";

	sprite_fragment_shader = "shaders/sprite.frag";
	sprite_vertex_shader = "shaders/sprite.vert";

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
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(_window, window_width / 2, window_height / 2);

	// background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
	programID = shader->LoadShaders(sprite_vertex_shader.c_str(), sprite_fragment_shader.c_str());
	fullbrightID = shader->LoadShaders(fullbright_vertex_shader.c_str(), fullbright_fragment_shader.c_str());


	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexUVID = glGetAttribLocation(programID, "vertexUV");
	vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
	modelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");

	// Get a handle for our "myTextureSampler" uniform
	diffuseTextureID = glGetUniformLocation(programID, "DiffuseTextureSampler");
	normalTextureID = glGetUniformLocation(programID, "NormalTextureSampler");
	specularTextureID = glGetUniformLocation(programID, "SpecularTextureSampler");

	// Get a handle for our "myTextureSampler" uniform
	textureID = glGetUniformLocation(programID, "myTextureSampler");

	// Get a handle for our "LightPosition_worldspace" uniform
	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	return 0;
}

void Renderer::renderScene(Scene* scene)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// get viewMatrix and projectionMatrix from Camera (Camera position and direction)
	ViewMatrix = scene->camera()->getViewMatrix();
	ProjectionMatrix = scene->camera()->getProjectionMatrix();

	if (scene->sky() != NULL) {
		//render the Background
		this->renderSkydome(scene->sky());
	}

	std::vector<Sprite*> sprites = scene->spritechildren();
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i] != NULL) {
			// render the Sprite 
			this->renderSprite(sprites[i]);
		}
	}

	//use our standard shaders
	glUseProgram(programID);

	// see if we need to render anything
	std::vector<Model*> models = scene->modelchildren();
	for (int i = 0; i < models.size(); i++) {
		if (models[i] != NULL) {
			// render the Model 
			this->renderModel(models[i]);
		}
	}

	vec3 lightPos = vec3(10, 10, -50);
	glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

	// Swap buffers
	glfwSwapBuffers(_window);
	glfwPollEvents();
}


void Renderer::renderSkydome(Skydome* m) {
	mat4 ModelMatrix = mat4(1.0f);

	// Build the Model matrix
	mat4 translationMatrix = translate(mat4(1.0f), vec3(m->position.x, m->position.y, m->position.z));
	mat4 rotationMatrix = eulerAngleYXZ(m->rotation.x, m->rotation.y, m->rotation.z);
	mat4 scalingMatrix = scale(mat4(1.0f), vec3(m->scale.x, m->scale.y, m->scale.z));

	ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	glUseProgram(fullbrightID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);


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
		3,							  // size : x+y+z => 3
		GL_FLOAT,					  // type
		GL_FALSE,					  // normalized?
		0,							  // stride
		(void*)0					  // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, m->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,				    // The attribute we want to configure
		2,							// size : U+V => 2
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		0,							// stride
		(void*)0					// array buffer offset
		);

	glDrawArrays(GL_TRIANGLES, 0, m->vertices().size());

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
}


void Renderer::renderModel(Model* m)
{
	mat4 ModelMatrix = mat4(1.0f);


	// Build the Model matrix
	mat4 translationMatrix = translate(mat4(1.0f), vec3(m->position.x, m->position.y, m->position.z));
	mat4 rotationMatrix = eulerAngleYXZ(m->rotation.x, m->rotation.y, m->rotation.z);
	mat4 scalingMatrix = scale(mat4(1.0f), vec3(m->scale.x, m->scale.y, m->scale.z));

	ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;


	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



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
		3,							  // size : x+y+z => 3
		GL_FLOAT,					  // type
		GL_FALSE,					  // normalized?
		0,							  // stride
		(void*)0					  // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, m->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,				    // The attribute we want to configure
		2,							// size : U+V => 2
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		0,							// stride
		(void*)0					// array buffer offset
		);


	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(vertexNormal_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, m->normalbuffer());
	glVertexAttribPointer(
		vertexNormal_modelspaceID,      // attribute
		3,                                // size : x+y+z => 3
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);


	glDrawArrays(GL_TRIANGLES, 0, m->vertices().size());

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
	glDisableVertexAttribArray(vertexNormal_modelspaceID);
}

void Renderer::renderSprite(Sprite* s)
{
	mat4 ModelMatrix = mat4(1.0f);


	// Build the Model matrix
	mat4 translationMatrix = translate(mat4(1.0f), vec3(s->position.x, s->position.y, s->position.z));
	mat4 rotationMatrix = eulerAngleYXZ(s->rotation.x, s->rotation.y, s->rotation.z);
	mat4 scalingMatrix = scale(mat4(1.0f), vec3(s->scale.x, s->scale.y, s->scale.z));

	ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;


	glUseProgram(fullbrightID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

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

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(vertexNormal_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, s->normalbuffer());
	glVertexAttribPointer(
		vertexNormal_modelspaceID,      // attribute
		3,                                // size : x+y+z => 3
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
	glDisableVertexAttribArray(vertexNormal_modelspaceID);

}