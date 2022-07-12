///*****Description*****
///アニメーションに関するクラス
///インスタンス生成時にアニメーションの情報を取得
/// そのアニメーションの更新、描画処理を行う
///*********************#pragma once
#include"../dxlib_ext/dxlib_ext.h"
#include<string>
#include<vector>

class GameManager;

class Animation {
public:
	Animation() {};
	//URL,描画中心,更新速度,最大枚数,横分割枚数,縦分割枚数,横画像サイズ,縦画像サイズ
	Animation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize);
	~Animation();

	//アニメーション更新
	void Update();
	//アニメーション描画
	void Draw();
	//アニメーションが終了しているか取得する関数
	inline bool GetIsAlive() {
		return isAlive;
	}

private:
	GameManager* gManager = nullptr;
	//画像ハンドル
	std::vector<int>animGh = {};

	//描画座標
	tnl::Vector3 pos;
	//コマ更新フレーム数
	int actSpeed = 0;
	//コマ最大数
	int maxMotionIndex = 0;
	//現在のフレームカウント
	int actWait = actSpeed;
	//選択中の画像インデックス
	int actIndex = 0;
	//描画する画像
	int drawGh = 0;


	//アニメーションの終了確認フラグ
	bool isAlive = true;
};