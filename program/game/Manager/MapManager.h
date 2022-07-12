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

	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static MapManager* Instance();

	//�O������}�b�v�������ĂԊ֐�
	void CreateMap(int MapId);

	//���݂̃}�b�v�̔ԍ����擾���`�悷��֐�
	void DrawNowMap(int NowMapNum);

	//debug �p�X�z��̒��g���擾
	inline std::vector < std::vector<std::string>>& GetPassVector() {
		return MapCsvPass;
	}

private:

	//�V���O���g���C���X�^���X
	static MapManager* instance;

	//GameManagerInstance
	GameManager* gManager = nullptr;

	//���ݐ�������Ă���}�b�v�̔z��
	//std::vector<std::shared_ptr<Map>>createdMap;

	//std::shared_ptr<Map> createdMap[static_cast<uint32_t>(GameManager::MAP::MAX)] = {};

	std::shared_ptr<Map>* createdMap = nullptr;
	/*
		GLOBAL,
		FIRSTTOWN,
		SECONDTOWN,
		DUNGEON,
	*/

	//�O���[�o���}�b�v�̐���
	void CreateGlobalMap();
	//1�ڂ̊X�̃}�b�v�̐���
	void CreateFirstTownMap();
	//2�ڂ̊X�̃}�b�v�̐���
	void CreateSecondTownMap();
	//�_���W�����̃}�b�v�̐���
	void CreateDungeonMap();

	//�}�b�v�����֐��̔z��
	std::function< void(MapManager*) > MapCreater[4] = { &MapManager::CreateGlobalMap,&MapManager::CreateFirstTownMap,
														&MapManager::CreateSecondTownMap,&MapManager::CreateDungeonMap };

	//�}�b�v�ǂݍ��݂̂��߂̃p�X�z��
	std::vector < std::vector<std::string>> MapCsvPass;

};

