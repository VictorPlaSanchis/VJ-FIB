#include "ObjectKey.h"
#include "SceneManagement.h"

using namespace glm;

void ObjectKey::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	int numberOfFramesX = 1;
	int numberOfFramesY = 1;

	spritesheet.loadFromFile("images/key.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 8), glm::vec2(1. / numberOfFramesX, 1. / numberOfFramesY), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void ObjectKey::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void ObjectKey::behaviour()
{
	SceneManagement::instance().currentScene->openDoor();
	isDestroyed = true;
}
