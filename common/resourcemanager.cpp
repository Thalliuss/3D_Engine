#include "resourcemanager.h"

ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{

}

Entity* ResourceManager::getEntity(Entity* e, std::string filename) {
	return e;
}

GLuint ResourceManager::getTexture(std::string filename){	
	if (_textures[filename] != NULL) {
		return _texture = _textures[filename];
	}	
	else {
		Texture* t = new Texture();
		return _textures[filename] = t->loadDDS(filename.c_str());
	}
	return NULL;
}