#include "TitleScene.h"
#include"../Manager/MapManager.h"
#include"../Manager/GameManager.h"
#include"../Camera.h"
#include"../Object/Player.h"

TitleScene::TitleScene()
{
	gManager = GameManager::Instance();
	mManager = MapManager::Instance();

	camera = std::make_shared<Camera>();

	mManager->CreateMap(static_cast<uint32_t>(GameManager::MAP::GLOBAL));

	player = gManager->GetPlayer();

	liveObjects = gManager->GetObjectList();
	//MapCsvPass = mManager->GetPassVector();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	camera->CameraMove(player->GetPos());

	for (auto object : liveObjects) {
		object->Update();
	}
}

void TitleScene::Draw()
{
	//debug 本来は現在のマップを表す変数を一つ作っておく
	mManager->DrawNowMap(static_cast<uint32_t>(GameManager::MAP::GLOBAL));

	for (auto object : liveObjects) {
		object->Draw();
	}
}
