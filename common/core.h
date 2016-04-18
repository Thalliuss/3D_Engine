#ifndef CORE_H
#define CORE_H

#include <common/scene.h>
#include <common/renderer.h>

class Core
{
public:
	Core();
	~Core();
	Renderer renderer() { return _renderer; }
	void run(Scene* scene);

private:
	Renderer _renderer;
	double _deltaTime;
};



#endif // !CORE_H
