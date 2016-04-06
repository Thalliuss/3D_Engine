#ifndef SCENE01_H
#define SCENE01_H

#include <common/scene.h>
#include <common/entity.h>
#include <common/skydome.h>


class Scene01 : public Scene
{
public:
	Scene01();
	~Scene01();
private:
	Sprite* sprite;
	Model* cube;
	Skydome* skydome;
};

#endif // !SCENE01_H

