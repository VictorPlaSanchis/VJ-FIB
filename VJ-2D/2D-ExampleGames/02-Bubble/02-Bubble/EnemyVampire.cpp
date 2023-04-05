#include "EnemyVampire.h"
#include <stdlib.h>
#include <time.h>

#define FALL_STEP 4
#define VELOCITY 1
#define initialValueFramesToChangeDirection 200

using namespace glm;

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void EnemyVampire::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	srand(time(NULL));
	int numberOfFramesX = 6;
	int numberOfFramesY = 2;

	float animationSpeed = 2.5;

	spritesheet.loadFromFile("images/vampire.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 22), glm::vec2(1. / numberOfFramesX, 1. / numberOfFramesY), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 16);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.5));

	sprite->setAnimationSpeed(STAND_RIGHT, 16);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0, 0.0));

	sprite->setAnimationSpeed(MOVE_LEFT, numberOfFramesX * animationSpeed);
	float factor = 1.0 / numberOfFramesX;
	for (int i = 0; i < numberOfFramesX; i++) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(factor * i, 0.5));
	}

	sprite->setAnimationSpeed(MOVE_RIGHT, numberOfFramesX * animationSpeed);
	factor = 1.0 / numberOfFramesX;
	for (int i = 0; i < numberOfFramesX; i++) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(factor * i, 0.0));
	}

	this->currentState = NORMAL;
	this->currentDirection = GOING_LEFT;
	this->framesToChangeDirection = initialValueFramesToChangeDirection;
	sprite->changeAnimation(MOVE_LEFT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void EnemyVampire::update(int deltaTime) {

	if (this->framesToChangeDirection <= 0) {
		this->framesToChangeDirection = initialValueFramesToChangeDirection;
		if (currentDirection == GOING_LEFT)
			currentDirection = FLY_LEFT_UP;
		if (currentDirection == GOING_RIGHT)
			currentDirection = FLY_RIGHT_UP;
		currentState = FLYING;
	}

	sprite->update(deltaTime);

	switch (currentState) {
		case NORMAL:

			this->framesToChangeDirection--;
			// GRAVITY + PING-PONG MOVEMENT
			posEnemy.y += FALL_STEP;
			if (!map->collisionMoveDown(posEnemy, glm::ivec2(16, 8), &posEnemy.y))
			{
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
			}
			else {
				if (currentDirection == GOING_LEFT) {
					posEnemy.x -= VELOCITY;
					if (map->collisionMoveLeft(posEnemy, vec2(16, 8))) {
						currentDirection = GOING_RIGHT;
						sprite->changeAnimation(MOVE_RIGHT);
						posEnemy.x += VELOCITY;
					}
				}
				else if (currentDirection == GOING_RIGHT) {
					posEnemy.x += VELOCITY;
					if (map->collisionMoveRight(posEnemy, vec2(16, 8))) {
						currentDirection = GOING_LEFT;
						sprite->changeAnimation(MOVE_LEFT);
						posEnemy.x -= VELOCITY;
					}
				}
			}
			break;

		case FLYING:

			// 4D-PING-PONG MOVEMENT

			int falsePos = 0;
			bool collisionMade = true;
			bool collisionDownMade = false;
			while (collisionMade) {
				collisionMade = false;
				collisionDownMade = false;
				switch (currentDirection) {
					case FLY_LEFT_UP:
						posEnemy.x -= VELOCITY;
						posEnemy.y -= VELOCITY;
						if (map->collisionMoveLeft(posEnemy, vec2(16, 5))) {
							currentDirection = FLY_RIGHT_UP;
							sprite->changeAnimation(MOVE_RIGHT);
							collisionMade = true;
						} else if (map->collisionMoveUp(posEnemy, vec2(12, 8))) {
							currentDirection = FLY_LEFT_DOWN;
							sprite->changeAnimation(MOVE_LEFT);
							collisionMade = true;
						}
						break;
					case FLY_LEFT_DOWN:
						posEnemy.x -= VELOCITY;
						posEnemy.y += VELOCITY;
						if (map->collisionMoveLeft(posEnemy, vec2(16, 5))) {
							currentDirection = FLY_RIGHT_DOWN;
							sprite->changeAnimation(MOVE_RIGHT);
							collisionMade = true;
						}
						else if (map->collisionMoveDown(posEnemy, vec2(12, 8), &falsePos)) {
							currentDirection = FLY_LEFT_UP;
							sprite->changeAnimation(MOVE_LEFT);
							collisionMade = true;
							collisionDownMade = true;
						}
						break;
					case FLY_RIGHT_UP:
						posEnemy.x += VELOCITY;
						posEnemy.y -= VELOCITY;
						if (map->collisionMoveRight(posEnemy, vec2(16, 5))) {
							currentDirection = FLY_LEFT_UP;
							sprite->changeAnimation(MOVE_LEFT);
							collisionMade = true;
						}
						else if (map->collisionMoveUp(posEnemy, vec2(12, 8))) {
							currentDirection = FLY_RIGHT_DOWN;
							sprite->changeAnimation(MOVE_RIGHT);
							collisionMade = true;
						}
						break;
					case FLY_RIGHT_DOWN:
						posEnemy.x += VELOCITY;
						posEnemy.y += VELOCITY;
						if (map->collisionMoveRight(posEnemy, vec2(16, 5))) {
							currentDirection = FLY_LEFT_DOWN;
							sprite->changeAnimation(MOVE_LEFT);
							collisionMade = true;
						}
						else if (map->collisionMoveDown(posEnemy, vec2(12, 8), &falsePos)) {
							currentDirection = FLY_RIGHT_UP;
							sprite->changeAnimation(MOVE_RIGHT);
							collisionMade = true;
							collisionDownMade = true;
						}
						break;
				}
				if (collisionDownMade) {
					int transform = rand() % 2;
					if (transform) {
						currentState = NORMAL;
						collisionMade = false;
						posEnemy.y -= VELOCITY;
						if (currentDirection == FLY_LEFT_UP || currentDirection == FLY_LEFT_DOWN)
							currentDirection = GOING_LEFT;
						if (currentDirection == FLY_RIGHT_UP || currentDirection == FLY_RIGHT_DOWN)
							currentDirection = GOING_RIGHT;
					}
				}
			}
			break;
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}