#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

#include "EnemySkeleton.h"
#include "EnemyVampire.h"

#include <vector>

#define SCREEN_X (320.0 / 2.0) - ((1.0 / 3.4) * 320.0)
#define SCREEN_Y 50

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

Scene::Scene(string file)
{
	map = NULL;
	player = NULL;
	enemies = list<Enemy*>();
	this->fileScene = file;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (enemies.size() > 0)
		for (Enemy* enemy : enemies)
			delete enemy;
}

void Scene::initVariables() {
	enemies = std::list<Enemy*>();
	objects = std::list<Object*>();
}

void Scene::init()
{
	initShaders();
	initVariables();
	map = TileMap::createTileMap(this->fileScene, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

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

	// Objects
	ObjectKey* key = new ObjectKey();
	key->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	key->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 3) * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	key->setTileMap(map);
	//objects.push_back(key);
	this->key = key;

	ObjectDoor* door = new ObjectDoor();
	door->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	door->setPosition(glm::vec2(6 * map->getTileSize(), 6 * map->getTileSize()));
	door->setTileMap(map);
	objects.push_back(door);
	this->door = door;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	map->update(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	for (Object* object : objects) {
		object->update(deltaTime);
	}
	for (Enemy* enemy : enemies) {
		enemy->update(deltaTime);
	}
	if (collisionPlayerEnemy() && !playerCannotDie) {
		// restar corazon
		SceneManagement::instance().restartCurrentScene();
	}

	Object* objectCollisioned = collisionPlayerObject();
	if (objectCollisioned != nullptr) {
		objectCollisioned->behaviour();
	}

	map->changePosition(this->player->posPlayer);
	if (this->map->allTilesColoured()) {
		makeAppearKey();
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
	for (Object* object : objects) {
		object->render();
	}
	for (Enemy* enemy : enemies) {
		enemy->render();
	}
}

float distance(glm::vec2 A, glm::vec2 B) {
	return glm::distance(A, B);
}

bool Scene::collisionPlayerEnemy()
{
	const float minimumDistance = 6.0f;
	glm::vec2 positionPlayer = this->player->posPlayer;
	for (Enemy* enemy : enemies) {
		glm::vec2 positionEnemy = enemy->posEnemy - glm::ivec2(0, 2);
		if (distance(positionPlayer, positionEnemy) < minimumDistance) {
			return true;
		}
	}
	return false;
}

Object* Scene::collisionPlayerObject()
{
	const float minimumDistance = 12.0f;
	glm::vec2 positionPlayer = this->player->posPlayer;
	for (Object* object : objects) {
		glm::vec2 positionObject = object->posObject;
		if (distance(positionPlayer, positionObject) < minimumDistance) {
			return object;
		}
	}
	return nullptr;
}

void Scene::openDoor()
{
	this->door->openDoor();
	this->haveKey = true;
}

void Scene::makeAppearKey()
{
	auto it = std::find(objects.begin(), objects.end(), key);
	if (it == objects.end()) {
		objects.push_back(this->key);
	}
}

void Scene::initShaders()
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



