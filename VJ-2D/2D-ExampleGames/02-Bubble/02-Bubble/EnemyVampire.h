#ifndef _ENEMY_VAMPIRE_INCLUDE
#define _ENEMY_VAMPIRE_INCLUDE

#include "Enemy.h"

class EnemyVampire : public Enemy {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);

	enum VampireDirection
	{
		GOING_RIGHT, GOING_LEFT, FLY_RIGHT_UP, FLY_LEFT_UP, FLY_RIGHT_DOWN, FLY_LEFT_DOWN
	};

	enum directions {
		R, L, U, D
	};

private:

	enum VampireState
	{
		NORMAL, FLYING
	};

	int framesToChangeDirection;

	VampireDirection currentDirection;
	VampireState currentState;

};

#endif // _ENEMY_VAMPIRE_INCLUDE