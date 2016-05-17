#ifndef SPRITE_H
#define SPRITE_H

#include <common/texture.h>
#include <common/entity.h>

class Sprite: public Entity
{
public:
	Sprite();
	virtual ~Sprite();

	void addTexture(const char* s);

private:
	std::string _lastDDS;

	bool isFirst;
};


#endif // !SPRITE_H
