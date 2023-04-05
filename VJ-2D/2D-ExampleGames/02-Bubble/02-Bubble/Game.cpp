#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	SceneManagement::instance().initializeScenes();
	goMenu();
}

void Game::goMenu() {
	menu.init();
	start = true;
	hearts = 0;
}

bool Game::update(int deltaTime)
{
	if (start) menu.update(deltaTime);
	else SceneManagement::instance().currentScene->update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (start) menu.render();
	else SceneManagement::instance().currentScene->render();
}

void Game::keyPressed(int key)
{
	if (key == 97)
		SceneManagement::instance().goNextScene();
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::changeMode(int mode) 
{
	switch (mode) {
	case 0:
		start = true;
		break;
	case 1:
		start = false;
		break;
	default:
		start = true;
	}
}





