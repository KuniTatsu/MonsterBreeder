#include "MapManager.h"
#include"GameManager.h"
#include"../Map.h"

MapManager::MapManager()
{
	gManager = GameManager::Instance();

	createdMap = new std::shared_ptr<Map>[static_cast<uint32_t>(GameManager::MAP::MAX)];


	//マップパスの読み込み
	auto loadCsv = tnl::LoadCsv("Csv/MapPass.csv");

	//1マップを構成する3つのcsvごとに配列を作る
	MapCsvPass.resize(((loadCsv.size() - 1) / 3));

	//配列の１次元目
	int arrayNum = 0;

	//Csvの読み込み
	for (int i = 1; i < loadCsv.size(); ++i) {

		auto pass = loadCsv[i][0];

		MapCsvPass[arrayNum].emplace_back(pass);

		//3つずつに分けるために3で割ったあまりで判定する
		if (i % 3 == 0)arrayNum++;
	}
}

MapManager::~MapManager()
{
	delete[] createdMap;
}

MapManager* MapManager::Instance()
{
	if (instance == nullptr) {
		instance = new MapManager();
	}
	return instance;
}

void MapManager::CreateMap(int MapId)
{
	MapCreater[MapId](this);
}

void MapManager::DrawNowMap(int NowMapNum)
{
	//createdMap[NowMapNum]
	createdMap[NowMapNum]->DrawMap();
}

void MapManager::CreateGlobalMap()
{
	auto newMap = std::make_shared<Map>(MapCsvPass[static_cast<uint32_t>(GameManager::MAP::GLOBAL)]);
	//createdMap.emplace_back(newMap);
	createdMap[static_cast<uint32_t>(GameManager::MAP::GLOBAL)] = newMap;
}

void MapManager::CreateFirstTownMap()
{
}

void MapManager::CreateSecondTownMap()
{
}

void MapManager::CreateDungeonMap()
{
}
