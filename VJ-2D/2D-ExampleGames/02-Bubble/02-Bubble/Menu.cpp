#include "Menu.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>

#include "EnemySkeleton.h"

#define SCREEN_X 32 * 4
#define SCREEN_Y 16 * 4

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

Menu::Menu()
{
	map = NULL;
	player = NULL;
	sprites = vector<Sprite*>();
}

Menu::~Menu()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (sprites.size() > 0)
		for (Sprite* s : sprites)
			delete s;
}


void Menu::init()
{
	up=false;
	down=false;
	right = false;
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	sel = 0;

	// Others
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	spritesheet.loadFromFile("images/SEL0.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1., 1.), &spritesheet, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.0));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));
	sprites.push_back(sprite);

	spritesheet1.loadFromFile("images/SEL1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1., 1.), &spritesheet1, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.0));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));
	sprites.push_back(sprite);

	spritesheet2.loadFromFile("images/SEL2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1., 1.), &spritesheet2, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.0));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));
	sprites.push_back(sprite);

	spritesheet3.loadFromFile("images/SEL3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1., 1.), &spritesheet3, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0, 0.0));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));
	sprites.push_back(sprite);
}

void Menu::update(int deltaTime)
{
	currentTime += deltaTime;
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		switch (sel)
		{
		case 0:
			Game::instance().changeMode(1);
			break;
		default:
			break;
		}
		
		right = true;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (!up){
			if (sel > 0)--sel;
		}
		up = true;
	}else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (!down) {
			if (sel < sprites.size() - 1) ++sel;
		}
		down = true;
	}
	else{
		right = false;
		up = false;
		down = false;
	}
	sprites[sel]->update(deltaTime);
}

void Menu::render()
{
	glm::mat4 modelview;
	
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	sprites[sel]->render();
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}