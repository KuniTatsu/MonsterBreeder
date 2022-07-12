#include "MapManager.h"
#include"GameManager.h"
#include"../Map.h"

MapManager::MapManager()
{
	gManager = GameManager::Instance();

	createdMap = new std::shared_ptr<Map>[static_cast<uint32_t>(GameManager::MAP::MAX)];


	//�}�b�v�p�X�̓ǂݍ���
	auto loadCsv = tnl::LoadCsv("Csv/MapPass.csv");

	//1�}�b�v���\������3��csv���Ƃɔz������
	MapCsvPass.resize(((loadCsv.size() - 1) / 3));

	//�z��̂P������
	int arrayNum = 0;

	//Csv�̓ǂݍ���
	for (int i = 1; i < loadCsv.size(); ++i) {

		auto pass = loadCsv[i][0];

		MapCsvPass[arrayNum].emplace_back(pass);

		//3���ɕ����邽�߂�3�Ŋ��������܂�Ŕ��肷��
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
