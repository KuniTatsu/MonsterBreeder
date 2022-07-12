#include <time.h>
#include <algorithm>
#include "game_main.h"
#include"Manager/GameManager.h"
#include"Manager/MapManager.h"
#include "../dxlib_ext/dxlib_ext.h"

bool init = false;

GameManager* GameManager::instance = nullptr;
MapManager* MapManager::instance = nullptr;


GameManager* gManager = nullptr;
void gameMain(float delta_time) {

	if (!init) {
		gManager = GameManager::Instance();

		gManager->initGameManager();
		init = true;
	}

	gManager->Update(delta_time);
	gManager->Draw(delta_time);

}

