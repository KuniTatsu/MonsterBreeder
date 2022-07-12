#pragma once
#include<string>
#include<vector>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class Element;

class Menu
{
public:
	Menu() {};
	Menu(int MenuTopX, int MenuTopY, int Width,
		int Height, std::string GhPath);
	virtual~Menu() {};

	//背景描画
	void MenuDraw();

	//左上座標取得
	inline const tnl::Vector3& GetTopPos() {
		return menuTopPos;
	}

	//幅取得
	inline const int& GetWidth() {
		return width;
	}

	//高さ取得
	inline const int& GetHeight() {
		return height;
	}

protected:
	//メニュー左上座標
	tnl::Vector3 menuTopPos = {};

	//メニュー横幅
	int width = 0;
	//メニュー縦幅
	int height = 0;

	//メニュー背景画像パス
	std::string menuBackGroundGhPass = "";
	//メニュー背景画像ハンドル
	std::vector<int >menuBackGroundGh = {};

	GameManager* gManager = nullptr;
};

class SelectMenu :public Menu
{
public:
	SelectMenu(int TopX, int TopY, int Width, int Height, std::string GhPath);
	~SelectMenu();

	//menu項目追加
	void AddMenuElements(std::string Text);

	//menu選択関数
	bool MenuUpdate();

	//menuクリック検知関数
	bool CheckMenuClick();

	//menu描画関数
	void DrawSelectMenu();

	//メニュー選択番号を取得する関数
	inline int& GetNowSelectNum() {
		return nowSelectNum;
	}

	//メニュー番号をリセットする関数
	inline void	ResetMenuNum() {
		nowSelectNum = 0;
	}

private:

	////メニュー項目
	//std::vector <std::string>menuElements;

	//選択中のメニュー番号
	int nowSelectNum = 0;

	//メニュー項目表示のための左上からのオフセット距離
	const tnl::Vector3 OFFSET = { 10,10,0 };

	//メニュー項目表示のための各項目間距離
	const int DISTANCE = 20;


	//メニュー項目のハイライト画像ハンドル
	int highLightGh = 0;

	//menuElementのポインタ配列
	std::vector<std::unique_ptr<Element>>elements;

};

//--------------Menu項目,背景画像,当たり判定用クラス--------------//
class Element
{
public:
	Element(float CenterX, float CenterY, std::string Text);
	~Element();
	//メニュー項目の描画
	void DrawElement();



	//メニュー項目のクリック検知
	bool isClickElement();

	//中心座標
	tnl::Vector3 centerPos = {};

	//左端の座標
	tnl::Vector3 leftPos = {};

	//描画するテキスト
	std::string element="";

	//描画画像 50x20
	int gh = 0;

	//テキストエリアの大きさ
	const tnl::Vector3 TEXTRECT = { 100,20,0 };

	//gamemanager
	GameManager* gManager = nullptr;
};

