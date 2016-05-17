#ifndef SCENE02_H
#define SCENE02_H

#include <common/scene.h>

class Scene02 : public Scene
{
public:
	Scene02();
	virtual ~Scene02();
	virtual void update(float deltaTime);

private:
	Skydome* skydome;
	Model* cube;
	Sprite* sprite;
};

#endif // !SCENE02_H

