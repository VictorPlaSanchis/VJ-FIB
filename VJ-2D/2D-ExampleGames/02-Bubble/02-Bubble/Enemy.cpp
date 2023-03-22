#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 & pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}
