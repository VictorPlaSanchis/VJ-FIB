#ifndef _OBJECT_SPEED_INCLUDE
#define _OBJECT_SPEED_INCLUDE

#include "Object.h"

class ObjectSpeed : public Object {

private:

	bool isOpen = false;

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void behaviour();

};

#endif // _OBJECT_SPEED_INCLUDE