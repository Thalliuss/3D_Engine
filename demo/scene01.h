#ifndef SCENE01_H
#define SCENE01_H

#include <common/scene.h>
#include <common/sprite.h>

class Scene01 : public Scene
{
public:
	Scene01();
	~Scene01();
private:
	Sprite* s;
	Object* o;
	Object* sphere;
	Object* cube;
};

#endif // !SCENE01_H

