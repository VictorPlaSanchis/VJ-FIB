#include "SceneManagement.h"
#include "Game.h"


void SceneManagement::initializeScenes()
{
	int numLevels = 3;
	string filePrefix = "levels/level0";
	string extension = ".txt";
	for (int i = 1; i <= numLevels; i++) {
		string newSceneFile = filePrefix + std::to_string(i) + extension;
		Scene* newScene = new Scene(newSceneFile);
		newScene->init();
		this->scenes.push_back(newScene);
	}
	this->currentScene = scenes[0];
}

void SceneManagement::goNextScene()
{
	this->currentSceneIndex++;
	if (this->currentSceneIndex >= this->scenes.size())
		goMenu();
	this->currentScene = this->scenes[currentSceneIndex];
	this->currentScene->init();
}

void SceneManagement::goPreviousScene()
{
}

void SceneManagement::goFirstScene()
{
}

void SceneManagement::goLastScene()
{
}

void SceneManagement::goScene(int index)
{
	this->currentSceneIndex = index;
	this->currentScene = this->scenes[index];
	this->currentScene->init();
}

void SceneManagement::goMenu()
{
	this->currentSceneIndex = 0;
	this->currentScene = this->scenes[currentSceneIndex];
	Game::instance().goMenu();
}

void SceneManagement::restartCurrentScene() {
	this->currentScene->init();
}
