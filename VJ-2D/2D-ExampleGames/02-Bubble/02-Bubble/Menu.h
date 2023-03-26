#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Texture.h"

using namespace std;


class Menu
{

public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap* map;
	Player* player;
	vector<Sprite*> sprites;
	Sprite* sprite;
	Texture spritesheet;
	Texture spritesheet1;
	Texture spritesheet2;
	Texture spritesheet3;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int sel;
	bool up;
	bool down;
	bool right;
};

#endif 
