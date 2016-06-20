#ifndef CHUNK_H
#define CHUNK_H

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "common/model.h"
#include "common/scene.h"
#include "vector"

#include "common/resourcemanager.h"

class Chunk {
public:
	std::vector<Model*> voxels;

	Chunk();
	virtual ~Chunk(); 
	void create(Scene* s, glm::vec3 size);

private:
	Model* m;
	ResourceManager rm;
	vec3 position;	
	int top;
};

#endif //!CHUNK_H