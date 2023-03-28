#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

#include "EnemySkeleton.h"
#include "EnemyVampire.h"

#include <vector>

#define SCREEN_X 32 * 4
#define SCREEN_Y 16 * 4

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 8

#define ENEMY_1_INIT_X_TILES 4
#define ENEMY_1_INIT_Y_TILES 8

#define ENEMY_2_INIT_X_TILES 5
#define ENEMY_2_INIT_Y_TILES 6


Scene::Scene()
{
	map = NULL;
	player = NULL;
	enemies = list<Enemy*>();
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (enemies.size() > 0)
		for (Enemy* enemy : enemies)
			delete enemy;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	// Set up enemies on the level
	std::vector<string> enemiesFound;
	std::vector<int> enemiesX;
	std::vector<int> enemiesY;
	map->getEnemies(&enemiesFound, &enemiesX, &enemiesY);

	for (int i = 0; i < enemiesFound.size(); i++) {
		Enemy* enemy;
		if (enemiesFound[i] == "S") {
			enemy = new EnemySkeleton();
			enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			enemy->setPosition(glm::vec2(enemiesX[i] * map->getTileSize(), enemiesY[i] * map->getTileSize()));
			enemy->setTileMap(map);
			enemies.push_back(enemy);
		}
		else if (enemiesFound[i] == "V") {
			enemy = new EnemyVampire();
			enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			enemy->setPosition(glm::vec2(enemiesX[i] * map->getTileSize(), enemiesY[i] * map->getTileSize()));
			enemy->setTileMap(map);
			enemies.push_back(enemy);
		}
		else if (enemiesFound[i] == "W") {
			enemy = new EnemyVampire();
			enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			enemy->setPosition(glm::vec2(enemiesX[i] * map->getTileSize(), enemiesY[i] * map->getTileSize()));
			enemy->setTileMap(map);
			enemies.push_back(enemy);
		}
	}

	// Player
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	// Others
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	for (Enemy* enemy : enemies) {
		enemy->update(deltaTime);
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	for (Enemy* enemy : enemies) {
		enemy->render();
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



