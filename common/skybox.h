#ifndef SKYBOX_H
#define SKYBOX_H

#include "common/model.h"

class Skybox: public Model
{
public:
	Skybox();
	virtual ~Skybox();
	void addTexture(const char* s);

private:
};

#endif // !SKYBOX_H
