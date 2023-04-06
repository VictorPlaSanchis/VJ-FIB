#include "ObjectStopwatch.h"
#include "SceneManagement.h"

using namespace glm;

void ObjectStopwatch::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	int numberOfFramesX = 1;
	int numberOfFramesY = 1;

	spritesheet.loadFromFile("images/reloj.png", TEXTURE_PIXEL_FORMAT_RGBA);
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

void ObjectStopwatch::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void ObjectStopwatch::behaviour()
{
	SceneManagement::instance().currentScene->stopTime();
	SceneManagement::instance().currentScene->removeObject(this);
}
