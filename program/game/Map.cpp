#include "Map.h"
#include"Manager/GameManager.h"

Map::Map(std::vector<std::string>& MapPass)
{
	gManager = GameManager::Instance();

	//�p�X�̎擾
	for (int i = 0; i < 3; ++i) {
		csvPass[i] = MapPass[i];
	}
	LoadMap();

	//�}�b�v�`�b�v�̉摜�n���h���̎擾
	gManager->LoadDivGraphEx("graphics/mapchip.png", 128, 8, 16, 32, 32, mapGh);
}

Map::~Map()
{
}

void Map::DrawMap()
{
	DrawVecterMap(backMap);
	DrawVecterMap(objectMap);
}
/*
tnl::Vector3 Map::LocalToGlobal(tnl::Vector3 LocalPos)
{
	return tnl::Vector3();
}

tnl::Vector3 Map::GlobalToLocal(tnl::Vector3 LocalPos)
{
	return tnl::Vector3();
}
*/

void Map::LoadMap()
{
	//�w�i���C���[�̓ǂݍ���
	auto background = tnl::LoadCsv(csvPass[static_cast<uint32_t>(MAP::BACKGROUND)]);

	backMap.resize(background.size());

	for (int i = 0; i < background.size(); ++i) {
		for (int k = 0; k < background[i].size(); ++k) {
			backMap[i].emplace_back(std::stoi(background[i][k]));
		}
	}

	//�I�u�W�F�N�g���C���[�̓ǂݍ���
	auto object = tnl::LoadCsv(csvPass[static_cast<uint32_t>(MAP::OBJECT)]);

	objectMap.resize(object.size());

	for (int i = 0; i < object.size(); ++i) {
		for (int k = 0; k < object[i].size(); ++k) {
			objectMap[i].emplace_back(std::stoi(object[i][k]));
		}
	}

	//hit���C���[�̓ǂݍ���
	auto hit = tnl::LoadCsv(csvPass[static_cast<uint32_t>(MAP::HIT)]);

	hitMap.resize(hit.size());

	for (int i = 0; i < hit.size(); ++i) {
		for (int k = 0; k < hit[i].size(); ++k) {
			hitMap[i].emplace_back(std::stoi(hit[i][k]));
		}
	}

}

void Map::DrawVecterMap(std::vector<std::vector<int>>& LoadedMap)
{
	int x = CHIPSIZE >> 1;
	int y = CHIPSIZE >> 1;

	for (int i = 0; i < LoadedMap.size(); ++i) {
		for (int k = 0; k < LoadedMap[i].size(); ++k) {

			if (LoadedMap[i][k] == -1) {
				x += CHIPSIZE;
				continue;
			}
			DrawRotaGraph(x, y, 1, 0, mapGh[LoadedMap[i][k]], true);
			x += CHIPSIZE;
		}
		x = CHIPSIZE >> 1;
		y += CHIPSIZE;
	}


}
