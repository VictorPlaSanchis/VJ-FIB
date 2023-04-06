#include "EnemyWomper.h"

#define FALL_STEP 4
#define VELOCITY 1
#define initialValueFramesToJump 100
#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 36

using namespace glm;

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void EnemyWomper::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	int numberOfFramesX = 12;
	int numberOfFramesY = 2;

	spritesheet.loadFromFile("images/womper.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 22), glm::vec2(1. / numberOfFramesX, 1. / numberOfFramesY), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.5));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0, 0.0));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5));

	sprite->setAnimationSpeed(MOVE_LEFT, numberOfFramesX * 2);
	float factor = 1.0 / numberOfFramesX;
	for (int i = 0; i < numberOfFramesX; i++) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(factor * i, 0.5));
	}

	sprite->setAnimationSpeed(MOVE_RIGHT, numberOfFramesX * 2);
	factor = 1.0 / numberOfFramesX;
	for (int i = 0; i < numberOfFramesX; i++) {
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(factor * i, 0.0));
	}

	sprite->changeAnimation(MOVE_RIGHT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	this->framesToJump = initialValueFramesToJump;
}

void EnemyWomper::update(int deltaTime)
{
	sprite->update(deltaTime);
	int falsePointer;

	if (this->framesToJump <= 0) {
		if (map->collisionMoveDown(posEnemy, glm::ivec2(14, 10), &posEnemy.y))
		{
			this->framesToJump = initialValueFramesToJump;
			bJumping = true;
			jumpAngle = 0;
			startY = posEnemy.y;
		}
	}

	posEnemy.y += FALL_STEP;
	if (!map->collisionMoveDown(posEnemy, glm::ivec2(16, 8), &posEnemy.y))
	{
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	}
	else {
		if (currentDirection == SkeletonDirection::GOING_LEFT) {
			posEnemy.x -= VELOCITY;
			if (map->collisionMoveLeft(posEnemy, vec2(16, 8))) {
				currentDirection = SkeletonDirection::GOING_RIGHT;
				sprite->changeAnimation(MOVE_RIGHT);
				posEnemy.x += VELOCITY;
			}
		}
		else if (currentDirection == SkeletonDirection::GOING_RIGHT) {
			posEnemy.x += VELOCITY;
			if (map->collisionMoveRight(posEnemy, vec2(16, 8))) {
				currentDirection = SkeletonDirection::GOING_LEFT;
				sprite->changeAnimation(MOVE_LEFT);
				posEnemy.x -= VELOCITY;
			}
		}
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posEnemy.y = startY;
		}
		else
		{
			posEnemy.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posEnemy, glm::ivec2(16, 8), &falsePointer);
		}
	}
	else {
		this->framesToJump--;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}