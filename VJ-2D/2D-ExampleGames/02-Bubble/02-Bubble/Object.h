#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Object {

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void behaviour() = 0;
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

public:
	glm::ivec2 tileMapDispl, posObject;

	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool isDestroyed = false;

	bool collisionWithPlayer(glm::vec2 playerPosition);

};


#endif // _OBJECT_INCLUDE 
