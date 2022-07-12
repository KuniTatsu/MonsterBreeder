#pragma once
#include<vector>
#include<string>
#include"../dxlib_ext/dxlib_ext.h"

class GameManager;

class Map
{
public:
	Map(std::vector<std::string>& MapPass);
	~Map();

	//�}�b�v�̕`��
	void DrawMap();

	const int CHIPSIZE = 32;

	////���[�J�����W���`����W�̕ϊ�
	//tnl::Vector3 LocalToGlobal(tnl::Vector3 LocalPos);
	////�`����W�����[�J�����W�̕ϊ�
	//tnl::Vector3 GlobalToLocal(tnl::Vector3 LocalPos);
private:

	GameManager* gManager = nullptr;

	//Map���[�h�֐�
	void LoadMap();

	//Map�`�b�v�̉摜�n���h��
	std::vector<int>mapGh;

	enum class MAP :uint32_t {
		BACKGROUND,
		OBJECT,
		HIT,
		MAX
	};


	//Map���\������csv�̃p�X
	std::string csvPass[static_cast<uint32_t>(MAP::MAX)] = { "","","" };

	//�ǂݍ��񂾃}�b�v�`�b�v�ԍ��̓񎟌��z��
	//�w�i���C���[
	std::vector<std::vector<int>>backMap;
	//�I�u�W�F�N�g���C���[:�X,���Ȃ�
	std::vector<std::vector<int>>objectMap;
	//�����蔻��
	std::vector<std::vector<int>>hitMap;


	//�n���ꂽ�񎟌��z�񂩂�}�b�v��`�悷��֐�
	void DrawVecterMap(std::vector<std::vector<int>>& LoadedMap);
};

