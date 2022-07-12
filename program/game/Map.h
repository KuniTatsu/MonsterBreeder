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

	//マップの描画
	void DrawMap();

	const int CHIPSIZE = 32;

	////ローカル座標→描画座標の変換
	//tnl::Vector3 LocalToGlobal(tnl::Vector3 LocalPos);
	////描画座標→ローカル座標の変換
	//tnl::Vector3 GlobalToLocal(tnl::Vector3 LocalPos);
private:

	GameManager* gManager = nullptr;

	//Mapロード関数
	void LoadMap();

	//Mapチップの画像ハンドル
	std::vector<int>mapGh;

	enum class MAP :uint32_t {
		BACKGROUND,
		OBJECT,
		HIT,
		MAX
	};


	//Mapを構成するcsvのパス
	std::string csvPass[static_cast<uint32_t>(MAP::MAX)] = { "","","" };

	//読み込んだマップチップ番号の二次元配列
	//背景レイヤー
	std::vector<std::vector<int>>backMap;
	//オブジェクトレイヤー:街,橋など
	std::vector<std::vector<int>>objectMap;
	//当たり判定
	std::vector<std::vector<int>>hitMap;


	//渡された二次元配列からマップを描画する関数
	void DrawVecterMap(std::vector<std::vector<int>>& LoadedMap);
};

