#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Enemy {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

public:
	glm::ivec2 tileMapDispl, posEnemy;
	int startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _ENEMY_INCLUDE 
