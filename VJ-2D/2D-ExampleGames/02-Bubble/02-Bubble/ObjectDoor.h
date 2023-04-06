#ifndef _OBJECT_DOOR_INCLUDE
#define _OBJECT_DOOR_INCLUDE

#include "Object.h"

class ObjectDoor : public Object {

private:

	bool isOpen = false;

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void behaviour();

	void openDoor();

};

#endif // _OBJECT_DOOR_INCLUDE