#include "GameManager.h"
#include"SceneManager.h"
#include"MapManager.h"
#include"../Object/Player.h"
#include"../UIEditor/UIEditor.h"
#include<string>
#include<time.h>
#include<random>

//#include"Item.h"
//#include "FadeControl.h"
//#include "SoundManager.h"

GameManager::GameManager()
{
	//tnl::DebugTrace("\n�R���X�g���N�^���Ă΂ꂽ��\n");
}

GameManager* GameManager::Instance()
{
	if (instance == nullptr) {
		instance = new GameManager();
	}
	return instance;
}

std::shared_ptr<Player>& GameManager::GetPlayer()
{
	if (player == nullptr) {
		//�b��@
		player = std::make_shared<Player>(0, 0);
		player->SetList();
	}
	return player;
}

GameManager::~GameManager()
{

}

tnl::Vector3 GameManager::LocalToWorld(tnl::Vector3 LocalPos)
{
	return { LocalPos.x * 32 + 16,LocalPos.y * 32 + 16,0 };
}

tnl::Vector3 GameManager::WorldToLocal(tnl::Vector3 WorldPos)
{
	return { (WorldPos.x) / 32,(WorldPos.y) / 32,0 };
}

void GameManager::Update(const float Deltatime)
{
	deltatime = Deltatime;
	//�}�E�X���W�擾
	GetMousePoint(&mousePosX, &mousePosY);

	//�}�E�X�X�N���[���ʎ擾
	mouseWheel = GetMouseWheelRotVol();  //�z�C�[���̉�]�ʎ擾

	SceneManager::Update();

}
void GameManager::Draw(const float Deltatime)
{
	SceneManager::Render();

	editor->Draw();
}

void GameManager::initGameManager()
{
	//sound = new Sound();
	//fControl = new FadeControl();

	deltatime = 0.0f;
	SRand(time(0));

	//�ŏ��̃V�[��������
	SceneManager::ChangeScene(SceneManager::SCENE::TITLE);

	mManager = MapManager::Instance();

	//debug
	editor = new UIEditor();

	editor->Init();
	editor->LoadUI("Csv/UI/SaveUI.csv");

//	editor->LoadFileResource();

}

int GameManager::LoadGraphEx(std::string Gh)
{
	//�摜�p�X��map������
	auto it = ghmap.find(Gh);
	//���łɃ��[�h����Ă���΃O���t�B�b�N�n���h����Ԃ�
	if (it != ghmap.end()) {
		return ghmap[Gh];
	}
	//���[�h����ĂȂ���ΐV�������[�h���ēo�^
	else {
		int loadgh = LoadGraph(Gh.c_str());
		ghmap.insert(std::make_pair(Gh, loadgh));
	}
	//�o�^�����O���t�B�b�N�n���h����Ԃ�
	return ghmap[Gh];
}

void GameManager::LoadDivGraphEx(const std::string Gh, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize, std::vector<int>& GhVector)
{
	int* buf = new int[AllNum];
	LoadDivGraph(Gh.c_str(), AllNum, WidthNum, HeightNum, XSize, YSize, buf);

	for (int i = 0; i < AllNum; ++i) {
		GhVector.emplace_back(buf[i]);
	}
	delete[] buf;

}
//�����ȗ��ł�DrawRotaGraph
void GameManager::DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag)
{
	DrawRotaGraph(X, Y, 1, 0, GrHandle, true);
}

//a����b�܂ł̒l���烉���_���Ɏ擾����
int GameManager::GetRandEx(int a, int b)
{
	if (a > b) {
		int diff = static_cast<int>(a - b);
		int random = static_cast<int>(GetRand(diff) + b);

		return random;
	}
	else {
		int diff = static_cast<int>(b - a);
		int random = static_cast<int>(GetRand(diff) + a);

		return random;
	}
	return 0;
}

int GameManager::GerRandomNumInWeight(const std::vector<int> WeightList)
{
	// �񌈒�I�ȗ���������->�����V�[�h�Ɏg��
	std::random_device rnd;
	//�����_���Ȑ������߂邽�߂̊֐��������߂�
	//�����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 GetRandom(rnd());

	//���A���e�B�����肷��
	int totalWeight = 0;
	int selected = 0;

	//totalWeight�����߂�
	for (int i = 0; i < WeightList.size(); ++i) {
		totalWeight += WeightList[i];
	}
	//���͈͂̈�l���z�����擾
	std::uniform_int_distribution<> Weight(0, totalWeight);
	//���A���e�B�������_���Ō��߂�
	int rand = Weight(GetRandom);

	//--------��������E�F�C�g��p�������I--------//
	//���I
	for (int i = 0; i < WeightList.size(); i++) {
		if (rand < WeightList[i]) {
			//����
			selected = i;
			break;
		}

		// ���̑Ώۂ𒲂ׂ�
		rand -= WeightList[i];
	}
	return selected;
}

bool GameManager::isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//�}�E�X�̍��W���l�p�`�̊O���Ȃ�return false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	//�l�p�`�̓��������N���b�N���Ă�����
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
		return true;
	}
	return false;
}

bool GameManager::OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//�}�E�X�̍��W���l�p�`�̊O���Ȃ�return false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	return true;
}

void GameManager::ChangeMoveKey(tnl::Input::eKeys newKey, int dir)
{
	//�z��v�f���O�Ȃ�ύX���Ȃ�
	if (dir >= static_cast<uint32_t>(KEYDIR::MAX) || dir < 0)return;

	nowDirKeys[dir] = newKey;
	tnl::DebugTrace("�V�����L�[�̐ݒ�:[%d]��", dir);

}
