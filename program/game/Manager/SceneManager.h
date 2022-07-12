#pragma once
#include "../Scene/Scene.h"

class Scene;

class SceneManager {
public:
	enum SCENE {
		TITLE,
		GLOBAL
	};

	static void ChangeScene(SCENE scene);     //
	static void Update();                     //
	static void Render();                     //

	static BaseScene* m_pScene;               //

	static void Save();
	static void Load();

};