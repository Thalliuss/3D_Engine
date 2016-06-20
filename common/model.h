#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <common/texture.h>
#include <common/entity.h>


class Model: public Entity
{
public:
	Model();
	virtual ~Model();

	void addMesh(const char* o, const char* t);

	bool loadOBJ(const char* path);

private:


	int _lastTexture;
	bool isFirst;
};

#endif // !MODEL_H

