#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include<string>
#include<vector>
#include<memory>

class GameManager;
class UIData;

class GraphicUI
{
public:
	//GraphicUI(tnl::Vector3 Pos, int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData>UIData);

	//フレーム内に画像を入れる場合
	GraphicUI(int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData>FrameData,int Type);
	//フレーム内に画像が無い場合(フレームのみの描画)
	GraphicUI(int FrameWidth, int FrameHeight, std::shared_ptr<UIData>FrameData,int Type);
	//フレームを引き伸ばさない場合
	//GraphicUI(std::string Pass, float CenterX, float CenterY);
	GraphicUI(std::string Pass, int FrameWidth, int FrameHeight, std::shared_ptr<UIData> FrameData,int Type);

	~GraphicUI();

	void Draw();

	//中心座標の取得
	inline tnl::Vector3& GetCenterPos() {
		return centerPos;
	}
	//UIの幅の取得
	inline int GetUIWidth() {
		return width;
	}

	//UIの高さの取得
	inline int GetUIHeight() {
		return height;
	}
	//UIの直下Y座標取得
	inline int GetUnderBottomPos() {
		return static_cast<int>(underBottomPosY);
	}

	//UIの左上の座標取得
	tnl::Vector3& GetLeftTopPos();

	//CSV出力の際のデータ取得関数
	std::string GetCsvStringData(int Id);

private:

	GameManager* gManager = nullptr;

	//枠UIのデータ 画像パス,総分割枚数,横枚数,縦枚数,横サイズ,縦サイズ
	std::shared_ptr<UIData> frameData = nullptr;

	//vectorへの分割ロード
	void LoadDivGraphEx(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize);

	//画像変更/再ロード関数
	void ReLoadDivGraphic(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize);
	void ReLoadGraphic(std::string Pass);

	//UI一つの左上描画座標
	tnl::Vector3 pos = {};

	//UI画像の中心描画座標
	tnl::Vector3 centerPos = {};

	//UIのタイプ　0:分割拡大,1:そのまま拡大なし
	int uiType = -1;

	enum class UITYPE:uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//UIの枠の横幅
	int width = 0;
	//UIの枠の縦幅
	int height = 0;

	//UIの枠の3分割した一辺の長さ
	int splitLength = 0;

	//枠直下のy座標
	float underBottomPosY = 0;

	//枠画像ハンドル
	std::vector<int>frameGh;

	//分割無し画像のパス
	std::string buttonPass = "";
	//分割無し画像のハンドル
	int buttonGh = 0;

	//枠内に描画するUI画像のパス
	std::string drawGraphicPass = "none";

	//枠内に描画するUI画像ハンドル
	int drawUIGh = -1;

	//枠の描画関数
	void DrawFrame();
};

class UIData
{
public:
	UIData(std::string GraphicPass, int AllNum, int WidthNum, int HeightNum, int XSize, int YSize, float PosX, float PosY);
	~UIData();

	//GraphicUIクラスからはprivateメンバ変数をアクセス出来る
	friend GraphicUI;

private:

	std::string pass = "";
	int allNum = 0;
	int widthNum = 0;
	int heightNum = 0;
	int xSize = 0;
	int ySize = 0;

	tnl::Vector3 leftTopPos = {};

};

