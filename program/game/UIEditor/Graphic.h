#pragma once
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

//------------概要----------------//
//UIEditorで使うUI画像を左端に並べるためのクラス
//位置情報とハンドル、大きさなどを保持する

class GameManager;

class Graphic {

public:
	//ghを使用した生成 幅と高さはデフォルト引数を入れているが多分使わない
	Graphic(tnl::Vector3 Pos, int Gh, int Width = 100, int Height = 100);
	//ファイルパスを使用した生成
	Graphic(tnl::Vector3 Pos, std::string Pass, int Width, int Height);

	//描画中心座標
	tnl::Vector3 pos = {};
	//グラフィックハンドル
	int gh = 0;
	//横幅
	int width = 0;
	//縦幅
	int height = 0;

	GameManager* gManager = nullptr;


};