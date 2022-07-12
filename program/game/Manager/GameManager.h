//�Q�[���S�̂��Ǘ�����}�l�[�W���N���X
//�V���O���g���ō���Ă���
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>

class SceneManager;
class MapManager;
class Object;
class Player;
class UIEditor;

class GameManager {

protected:
	GameManager();
	~GameManager();
public:
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static GameManager* Instance();

	//Player����
	std::shared_ptr<Player>& GetPlayer();

	/*
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

	//�t���[���b
	float deltatime = 0.0f;

	//��ʒ������W
	const tnl::Vector3 Center = { 512,384,0 };

	//�`����W���烏�[���h���W�ւ̕ϊ�
	tnl::Vector3 LocalToWorld(tnl::Vector3 LocalPos);
	//���[���h���W����`����W�ւ̕ϊ�
	tnl::Vector3 WorldToLocal(tnl::Vector3 WorldPos);


	void Update(const float Deltatime);
	void Draw(const float Deltatime);

	//GameManager�̏�����
	void initGameManager();

	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string Gh);

	//�������̘A�Ȃ����摜��vector�Ɋi�[����֐�
	void LoadDivGraphEx(const std::string Gh, const int AllNum, const int WidthNum, const int HeightNum,
		int XSize, int YSize, std::vector<int>& GhVector);

	//DrawRotaGraph�̒Z�k��
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);

	int GetRandEx(int a, int b);

	//�����Z���k�E�c�C�X�^�[���̗p�������K���z�����_���֐�
	int GerRandomNumInWeight(const std::vector<int>WeightList);

	//�l�p�`�̃}�E�X�N���b�N���m
	bool isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);

	//�l�p�`�̃}�E�X�͈͓����m
	bool OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);


	//�}�E�X���W
	int mousePosX = 0;
	int mousePosY = 0;

	//�}�E�X�X�N���[��
	int mouseWheel = 0;

	//UI����ׂ����
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

	//map���
	enum class MAP {
		GLOBAL,
		FIRSTTOWN,
		SECONDTOWN,
		DUNGEON,
		MAX
	};
	//�^�w�肠��@
	enum class KEYDIR:uint32_t {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
	//�L�[���m�֐��ɓn���ۂɎg���L�[�z��
	const tnl::Input::eKeys DIRKEYS[4] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,tnl::Input::eKeys::KB_DOWN,tnl::Input::eKeys::KB_LEFT };

	//�L�[�R���t�B�O�p�L�[�z��
	tnl::Input::eKeys nowDirKeys[4] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,tnl::Input::eKeys::KB_DOWN,tnl::Input::eKeys::KB_LEFT };

	//�ړ��L�[�̃R���t�B�O�ύX�֐�
	void ChangeMoveKey(tnl::Input::eKeys newKey, int dir);


	//�I�u�W�F�N�g���X�g�ւ̓o�^
	inline void AddObjectList(std::shared_ptr<Object>object) {
		objects.emplace_back(object);
	}

	//�I�u�W�F�N�g���X�g�̎擾
	inline std::list<std::shared_ptr<Object>>& GetObjectList() {
		return  objects;
	}

private:
	//�V���O���g���C���X�^���X
	static GameManager* instance;

	MapManager* mManager = nullptr;

	UIEditor* editor = nullptr;

	//Object�^�|�C���^���X�g
	std::list<std::shared_ptr<Object>>objects;

	//Player�C���X�^���X
	std::shared_ptr<Player>player = nullptr;
};