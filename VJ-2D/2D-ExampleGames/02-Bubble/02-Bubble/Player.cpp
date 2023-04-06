#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 36
#define FALL_STEP 4
#define VELOCITY_PLAYER 1 // pixels per frame

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	
	int numberOfFramesX = 12;
	int numberOfFramesY = 2;

	spritesheet.loadFromFile("images/frog.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 22), glm::vec2(1./numberOfFramesX, 1./numberOfFramesY), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.5));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0, 0.0));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5));

	sprite->setAnimationSpeed(MOVE_LEFT, numberOfFramesX * 2);
	float factor = 1.0 / numberOfFramesX;
	for (int i = 0; i < numberOfFramesX; i++)  {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(factor * i, 0.5));
	}

	sprite->setAnimationSpeed(MOVE_RIGHT, numberOfFramesX * 2);
	factor = 1.0 / numberOfFramesX;
	for (int i = 0; i < numberOfFramesX; i++) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(factor * i, 0.0));
	}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
void Player::update(int deltaTime)
{
	int faster;
	if (SceneManagement::instance().currentScene->playerFast == true) {
		faster = 20;
	}
	else faster = 0;

	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= VELOCITY_PLAYER;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(8, 8)))
		{
			posPlayer.x += VELOCITY_PLAYER;
			sprite->changeAnimation(STAND_LEFT);
		}
		map->changePosition(posPlayer);
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += VELOCITY_PLAYER;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(16, 8)))
		{
			posPlayer.x -= VELOCITY_PLAYER;
			sprite->changeAnimation(STAND_RIGHT);
		}
		map->changePosition(posPlayer);
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - (JUMP_HEIGHT + faster) * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(16, 8), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(16, 8), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




