#pragma once
#include<functional>
#include<string>
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class Map;

class MapManager
{
protected:
	MapManager();
	~MapManager();
public:

	//インスタンスがなければ生成、あれば返す関数
	static MapManager* Instance();

	//外部からマップ生成を呼ぶ関数
	void CreateMap(int MapId);

	//現在のマップの番号を取得し描画する関数
	void DrawNowMap(int NowMapNum);

	//debug パス配列の中身を取得
	inline std::vector < std::vector<std::string>>& GetPassVector() {
		return MapCsvPass;
	}

private:

	//シングルトンインスタンス
	static MapManager* instance;

	//GameManagerInstance
	GameManager* gManager = nullptr;

	//現在生成されているマップの配列
	//std::vector<std::shared_ptr<Map>>createdMap;

	//std::shared_ptr<Map> createdMap[static_cast<uint32_t>(GameManager::MAP::MAX)] = {};

	std::shared_ptr<Map>* createdMap = nullptr;
	/*
		GLOBAL,
		FIRSTTOWN,
		SECONDTOWN,
		DUNGEON,
	*/

	//グローバルマップの生成
	void CreateGlobalMap();
	//1つ目の街のマップの生成
	void CreateFirstTownMap();
	//2つ目の街のマップの生成
	void CreateSecondTownMap();
	//ダンジョンのマップの生成
	void CreateDungeonMap();

	//マップ生成関数の配列
	std::function< void(MapManager*) > MapCreater[4] = { &MapManager::CreateGlobalMap,&MapManager::CreateFirstTownMap,
														&MapManager::CreateSecondTownMap,&MapManager::CreateDungeonMap };

	//マップ読み込みのためのパス配列
	std::vector < std::vector<std::string>> MapCsvPass;

};

