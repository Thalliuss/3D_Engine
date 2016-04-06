#ifndef SKYDOME_H
#define SKYDOME_H

#include "common/model.h"

class Skydome: public Model
{
public:
	Skydome();
	virtual ~Skydome();
	bool skydome() { return _skydome; };

private:
	bool _skydome = false;
};

#endif // !SKYDOME_H
