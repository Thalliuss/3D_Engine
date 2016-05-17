#ifndef SCENE01_H
#define SCENE01_H

#include <common/scene.h>

class Scene01 : public Scene
{
public:
	Scene01();
	virtual ~Scene01();
	virtual void update(float deltaTime);

private:
	Skydome* skydome;
	Model* cube;
	Sprite* sprite;
};

#endif // !SCENE01_H

