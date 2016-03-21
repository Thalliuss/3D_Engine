// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "scene01.h"
#include <common/core.h>


int main( void )
{
	Core c;
	Scene01* s = new Scene01();

	int running = 1;
	while (running) {
		c.run(s);
		if (!s->isRunning()) { running = 0; } 
	}

	delete s;

	glfwTerminate();

	return 0;
}
