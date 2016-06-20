#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>

#include <common/texture.h>
#include <common/model.h>
#include <common/entity.h>
#include <tools/vector_tools.h>


class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	GLuint getTexture(std::string filename);
	Entity* getEntity(Entity* e, std::string filename);

private:
	std::map<std::string, GLuint> _textures;
	std::map<std::string, Entity*> _entitys;
	GLuint _texture;
	Entity* _entity;
};
#endif // !RESOURCEMANAGER_H
