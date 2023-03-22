#ifndef _ENEMY_SKELETON_INCLUDE
#define _ENEMY_SKELETON_INCLUDE

#include "Enemy.h"

class EnemySkeleton : public Enemy {

private:

	enum SkeletonDirection
	{
		GOING_RIGHT, GOING_LEFT
	};

	SkeletonDirection currentDirection;

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);

};

#endif // _ENEMY_SKELETON_DEFINE