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
	//tnl::DebugTrace("\nコンストラクタが呼ばれたよ\n");
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
		//暫定　
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
	//マウス座標取得
	GetMousePoint(&mousePosX, &mousePosY);

	//マウススクロール量取得
	mouseWheel = GetMouseWheelRotVol();  //ホイールの回転量取得

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

	//最初のシーンを決定
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
	//画像パスでmapを検索
	auto it = ghmap.find(Gh);
	//すでにロードされていればグラフィックハンドルを返す
	if (it != ghmap.end()) {
		return ghmap[Gh];
	}
	//ロードされてなければ新しくロードして登録
	else {
		int loadgh = LoadGraph(Gh.c_str());
		ghmap.insert(std::make_pair(Gh, loadgh));
	}
	//登録したグラフィックハンドルを返す
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
//引数省略版のDrawRotaGraph
void GameManager::DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag)
{
	DrawRotaGraph(X, Y, 1, 0, GrHandle, true);
}

//aからbまでの値からランダムに取得する
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
	// 非決定的な乱数生成器->初期シードに使う
	std::random_device rnd;
	//ランダムな数を求めるための関数名を決める
	//メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::mt19937 GetRandom(rnd());

	//レアリティを決定する
	int totalWeight = 0;
	int selected = 0;

	//totalWeightを求める
	for (int i = 0; i < WeightList.size(); ++i) {
		totalWeight += WeightList[i];
	}
	//一定範囲の一様分布乱数取得
	std::uniform_int_distribution<> Weight(0, totalWeight);
	//レアリティをランダムで決める
	int rand = Weight(GetRandom);

	//--------ここからウェイトを用いた抽選--------//
	//抽選
	for (int i = 0; i < WeightList.size(); i++) {
		if (rand < WeightList[i]) {
			//決定
			selected = i;
			break;
		}

		// 次の対象を調べる
		rand -= WeightList[i];
	}
	return selected;
}

bool GameManager::isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//マウスの座標が四角形の外側ならreturn false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	//四角形の内側かつ左クリックしていたら
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
		return true;
	}
	return false;
}

bool GameManager::OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom)
{
	//マウスの座標が四角形の外側ならreturn false
	if (MouseX<RectLeft || MouseX>RectRight || mousePosY<RectTop || mousePosY>RectBottom)return false;

	return true;
}

void GameManager::ChangeMoveKey(tnl::Input::eKeys newKey, int dir)
{
	//配列要素数外なら変更しない
	if (dir >= static_cast<uint32_t>(KEYDIR::MAX) || dir < 0)return;

	nowDirKeys[dir] = newKey;
	tnl::DebugTrace("新しいキーの設定:[%d]番", dir);

}
