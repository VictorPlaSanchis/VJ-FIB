#ifndef _OBJECT_KEY_INCLUDE
#define _OBJECT_KEY_INCLUDE

#include "Object.h"

class ObjectKey : public Object {

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void behaviour();

};

#endif // _OBJECT_KEY_INCLUDE