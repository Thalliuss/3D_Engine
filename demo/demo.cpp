// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "scene01.h"
#include "scene02.h"
#include <common/core.h>


int main( void )
{
	Core c;
	Scene01* s1 = new Scene01();
	Scene02* s2 = new Scene02();

	c.scenes.push_back(s1);
	c.scenes.push_back(s2);

	while (c.scenes[c.counter]->isRunning()) {
		c.run(c.scenes[c.counter]);
	}

	delete s1;
	delete s2;
	glfwTerminate();

	return 0;
}
