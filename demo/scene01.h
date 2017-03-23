#ifndef SCENE01_H
#define SCENE01_H

#include <common/scene.h>
#include <common/chunk.h>

class Scene01 : public Scene
{
public:
	Scene01();
	virtual ~Scene01();
	virtual void update(float deltaTime);

private:
	Skybox* sky;
	Chunk chunk;

};

#endif // !SCENE01_H

