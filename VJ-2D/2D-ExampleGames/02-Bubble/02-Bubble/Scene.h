#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <list>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Object.h"
#include "ObjectKey.h"
#include "ObjectDoor.h"

using namespace std;


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	Scene(string file);
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	TileMap* getTileMap() { return this->map; }

	bool collisionPlayerEnemy();
	Object* collisionPlayerObject();

	void openDoor();

private:
	void initShaders();
	void initVariables();

private:
	TileMap* map;
	Player* player;
	list<Enemy*> enemies;
	list<Object*> objects;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	string fileScene;

	bool haveKey = false;
	ObjectKey* key;
	ObjectDoor* door;

	glm::ivec2 doorPosition;
	glm::ivec2 keyPosition;

};


#endif // _SCENE_INCLUDE

