#ifndef _OBJECT_STOP_INCLUDE
#define _OBJECT_STOP_INCLUDE

#include "Object.h"

class ObjectStopwatch : public Object {

private:

	bool isOpen = false;

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void behaviour();

};

#endif // _OBJECT_STOP_INCLUDE