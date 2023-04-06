#include "ObjectDoor.h"
#include "SceneManagement.h"

using namespace glm;

void ObjectDoor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	int numberOfFramesX = 2;
	int numberOfFramesY = 1;

	spritesheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1. / numberOfFramesX, 1. / numberOfFramesY), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.0, 0.0));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.5, 0.0));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void ObjectDoor::openDoor() {
	isOpen = true;
	sprite->changeAnimation(1);
}

void ObjectDoor::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void ObjectDoor::behaviour()
{
	if (isOpen) {
		SceneManagement::instance().goNextScene();
	}
}
