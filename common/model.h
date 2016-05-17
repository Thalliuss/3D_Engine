#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <common/texture.h>
#include <common/entity.h>
using namespace std;


class Model: public Entity
{
public:
	Model();
	virtual ~Model();

	void addMesh(const char* o, const char* t);

	bool loadOBJ(
		const char* path,
		vector<vec3> & out_vertices,
		vector<vec2> & out_uvs,
		vector<vec3> & out_normals
	);
	void buffers();

private:
	bool isFirst;
	string _lastDDS;
	string _lastOBJ;
};

#endif // !MODEL_H

