#ifndef _SCENE_MANAGEMENT_INCLUDE
#define _SCENE_MANAGEMENT_INCLUDE

#include "Scene.h"
#include <vector>

class SceneManagement {

public:
	static SceneManagement& instance()
	{
		static SceneManagement S;
		return S;
	}

	void initializeScenes();
	void goNextScene();
	void goPreviousScene();
	void goFirstScene();
	void goLastScene();
	void goMenu();
	void restartCurrentScene();

public:
	std::vector<Scene*> scenes;
	Scene* currentScene;

private:
	int currentSceneIndex = 0;

};


#endif // _SCENE_MANAGEMENT_INCLUDE 
