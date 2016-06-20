#include "chunk.h"

Chunk::Chunk(){
	top = NULL;
}
Chunk::~Chunk(){

}



// Create a new Chunk of Model's
void Chunk::create(Scene* s, glm::vec3 size)
{
	for (int z = 0; z < size.z; z++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++) {
				m = new Model();
				position = vec3(x, y, z);

				s->addChild(m);
				m->position = position;

				voxels.push_back(m);

				if (y == size.y - 1) {
					m->addMesh("assets/cube.obj", "assets/uvmap.dds");
				}
				else {
					m->addMesh("assets/cube.obj", "assets/test.dds");
				}
			}
		}
	}
}

