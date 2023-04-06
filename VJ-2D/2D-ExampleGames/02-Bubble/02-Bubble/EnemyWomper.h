#ifndef _ENEMY_WOMPER_INCLUDE
#define _ENEMY_WOMPER_INCLUDE

#include "Enemy.h"

class EnemyWomper : public Enemy {

private:

	enum SkeletonDirection
	{
		GOING_RIGHT, GOING_LEFT
	};

	SkeletonDirection currentDirection;
	int framesToJump, jumpAngle;
	bool bJumping = false;

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);

};

#endif // _ENEMY_WOMPER_INCLUDE