#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <glfw3.h>

class Texture
{
public:
	// Load a .BMP file using our custom loader
	GLuint loadBMP_custom(const char * imagepath);

	//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
	//// or do it yourself (just like loadBMP_custom and loadDDS)
	//// Load a .TGA file using GLFW's own loader
	//GLuint loadTGA_glfw(const char * imagepath);

	// Load a .DDS file using GLFW's own loader
	GLuint loadDDS(const char * imagepath);

private:

};

#endif // !TEXTURE_H