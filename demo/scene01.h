#ifndef SCENE01_H
#define SCENE01_H

#include <common/scene.h>
#include <common/entity.h>

class Scene01 : public Scene
{
public:
	Scene01();
	~Scene01();
private:
	Sprite* sprite;
	Model* cube;
};

#endif // !SCENE01_H

