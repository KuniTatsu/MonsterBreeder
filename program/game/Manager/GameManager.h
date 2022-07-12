//ゲーム全体を管理するマネージャクラス
//シングルトンで作られている
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
	//インスタンスがなければ生成、あれば返す関数
	static GameManager* Instance();

	//Player生成
	std::shared_ptr<Player>& GetPlayer();

	/*
	FadeControl* fControl = nullptr;
	Sound* sound = nullptr;*/

	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

	//フレーム秒
	float deltatime = 0.0f;

	//画面中央座標
	const tnl::Vector3 Center = { 512,384,0 };

	//描画座標からワールド座標への変換
	tnl::Vector3 LocalToWorld(tnl::Vector3 LocalPos);
	//ワールド座標から描画座標への変換
	tnl::Vector3 WorldToLocal(tnl::Vector3 WorldPos);


	void Update(const float Deltatime);
	void Draw(const float Deltatime);

	//GameManagerの初期化
	void initGameManager();

	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string Gh);

	//複数枚の連なった画像をvectorに格納する関数
	void LoadDivGraphEx(const std::string Gh, const int AllNum, const int WidthNum, const int HeightNum,
		int XSize, int YSize, std::vector<int>& GhVector);

	//DrawRotaGraphの短縮版
	void DrawRotaGraphNormal(int X, int Y, int GrHandle, int TransFlag);

	int GetRandEx(int a, int b);

	//メルセンヌ・ツイスターを採用した正規分布ランダム関数
	int GerRandomNumInWeight(const std::vector<int>WeightList);

	//四角形のマウスクリック感知
	bool isClickedRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);

	//四角形のマウス範囲内感知
	bool OnMouseRect(int MouseX, int MouseY, int RectLeft, int RectTop, int RectRight, int RectBottom);


	//マウス座標
	int mousePosX = 0;
	int mousePosY = 0;

	//マウススクロール
	int mouseWheel = 0;

	//UIを並べる方向
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};

	//map種類
	enum class MAP {
		GLOBAL,
		FIRSTTOWN,
		SECONDTOWN,
		DUNGEON,
		MAX
	};
	//型指定あり　
	enum class KEYDIR:uint32_t {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
	//キー検知関数に渡す際に使うキー配列
	const tnl::Input::eKeys DIRKEYS[4] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,tnl::Input::eKeys::KB_DOWN,tnl::Input::eKeys::KB_LEFT };

	//キーコンフィグ用キー配列
	tnl::Input::eKeys nowDirKeys[4] = { tnl::Input::eKeys::KB_UP,tnl::Input::eKeys::KB_RIGHT,tnl::Input::eKeys::KB_DOWN,tnl::Input::eKeys::KB_LEFT };

	//移動キーのコンフィグ変更関数
	void ChangeMoveKey(tnl::Input::eKeys newKey, int dir);


	//オブジェクトリストへの登録
	inline void AddObjectList(std::shared_ptr<Object>object) {
		objects.emplace_back(object);
	}

	//オブジェクトリストの取得
	inline std::list<std::shared_ptr<Object>>& GetObjectList() {
		return  objects;
	}

private:
	//シングルトンインスタンス
	static GameManager* instance;

	MapManager* mManager = nullptr;

	UIEditor* editor = nullptr;

	//Object型ポインタリスト
	std::list<std::shared_ptr<Object>>objects;

	//Playerインスタンス
	std::shared_ptr<Player>player = nullptr;
};