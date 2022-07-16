#include "GraphicUI.h"
#include"../Manager/GameManager.h"

//GraphicUI::GraphicUI(tnl::Vector3 Pos, int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData>UIData)
//{
//	gManager = GameManager::Instance();
//
//	//枠のUIデータの代入
//	frameData = UIData;
//
//	//UIの左上の描画座標
//	pos = Pos;
//
//	//UI元画像の横幅取得
//	width = FrameWidth;
//
//	//UI元画像の縦幅取得
//	height = FrameHeight;
//
//	//3分割した長さを取得
//	splitLength = frameData->xSize;
//
//	//中心座標を取得
//	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);
//
//	underBottomPosY = centerPos.y + (height >> 1) + 50;
//
//	//枠の画像の分割ロード
//	//gManager->LoadDivGraphEx(FrameGh, 9, 3, 3, 16, 16, frameGh);
//	LoadDivGraphEx(frameData->pass, frameData->allNum, frameData->widthNum, frameData->heightNum,
//		frameData->xSize, frameData->ySize);
//
//	//枠内に描画するUI画像のロード
//	drawUIGh = gManager->LoadGraphEx(UIGh);
//}

//枠の中に画像を描画したい場合はこっちで生成する
GraphicUI::GraphicUI(int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData> FrameData)
{
	gManager = GameManager::Instance();

	//枠のUIデータの代入
	frameData = FrameData;

	//UI元画像の横幅取得
	width = FrameWidth;

	//UI元画像の縦幅取得
	height = FrameHeight;

	//3分割した長さを取得
	splitLength = frameData->xSize;

	//UIの左上の描画座標
	pos = frameData->leftTopPos;

	//中心座標を取得
	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);

	underBottomPosY = centerPos.y + (height >> 1) + 50;

	//枠の画像の分割ロード
	//gManager->LoadDivGraphEx(FrameGh, 9, 3, 3, 16, 16, frameGh);
	LoadDivGraphEx(frameData->pass, frameData->allNum, frameData->widthNum, frameData->heightNum,
		frameData->xSize, frameData->ySize);

	//枠内に描画するUI画像のロード
	drawUIGh = gManager->LoadGraphEx(UIGh);
}

//枠だけ欲しい場合はこっちで生成する
GraphicUI::GraphicUI(int FrameWidth, int FrameHeight, std::shared_ptr<UIData> FrameData)
{
	gManager = GameManager::Instance();

	//枠のUIデータの代入
	frameData = FrameData;

	//UI元画像の横幅取得
	width = FrameWidth;

	//UI元画像の縦幅取得
	height = FrameHeight;

	//3分割した長さを取得
	splitLength = frameData->xSize;

	//UIの左上の描画座標
	pos = frameData->leftTopPos;

	//中心座標を取得
	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);

	underBottomPosY = centerPos.y + (height >> 1) + 50;

	//枠の画像の分割ロード
	//gManager->LoadDivGraphEx(FrameGh, 9, 3, 3, 16, 16, frameGh);
	LoadDivGraphEx(frameData->pass, frameData->allNum, frameData->widthNum, frameData->heightNum,
		frameData->xSize, frameData->ySize);
}
//引き伸ばさない場合はこっちで生成する
GraphicUI::GraphicUI(std::string Pass, float CenterX, float CenterY)
{
	gManager = GameManager::Instance();
	buttonGh = gManager->LoadGraphEx(Pass);
	centerPos.x = CenterX;
	centerPos.y = CenterY;
}

GraphicUI::~GraphicUI()
{
}

void GraphicUI::Draw()
{
	//外枠の描画
	DrawFrame();
	//画像がなければ描画しない
	if (drawUIGh == -1)return;
	DrawRotaGraph(centerPos.x, centerPos.y, 0.98, 0, drawUIGh, true);
}
//画像のVectorへの分割ロード
void GraphicUI::LoadDivGraphEx(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize)
{
	//一時保管用の配列
	int* buf = new int[AllNum];
	//分割
	LoadDivGraph(Pass.c_str(), AllNum, WidthNum, HeightNum, XSize, YSize, buf);

	//vectorに格納
	for (int i = 0; i < AllNum; ++i) {
		frameGh.emplace_back(buf[i]);
	}
	//一時保管用配列の開放
	delete[] buf;
}

void GraphicUI::ReLoadDivGraphic(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize)
{
	//画像ハンドルの消去
	frameGh.clear();
	//画像の分割ロード
	LoadDivGraphEx(Pass, AllNum, WidthNum, HeightNum, XSize, YSize);
}

void GraphicUI::ReLoadGraphic(std::string Pass)
{
	buttonGh = 0;
	buttonGh = gManager->LoadGraphEx(Pass);
}

void GraphicUI::DrawFrame()
{
	//分割画像ではない場合はそのまま描画する
	if (frameGh.empty()) {
		DrawRotaGraph(centerPos.x, centerPos.y, 1, 0, buttonGh, true);
		return;
	}
	//枠の上段の描画
	DrawGraph(pos.x, pos.y, frameGh[0], true);
	DrawExtendGraph(pos.x + splitLength, pos.y, pos.x + width - splitLength, pos.y + splitLength, frameGh[1], true);
	DrawGraph(pos.x + width - splitLength, pos.y, frameGh[2], true);

	//枠の中段の描画
	DrawExtendGraph(pos.x, pos.y + splitLength, pos.x + splitLength, pos.y + height - splitLength, frameGh[3], true);
	DrawExtendGraph(pos.x + splitLength, pos.y + splitLength, pos.x + width - splitLength, pos.y + height - splitLength, frameGh[4], true);
	DrawExtendGraph(pos.x + width - splitLength, pos.y + splitLength, pos.x + width, pos.y + height - splitLength, frameGh[5], true);

	//枠の下段の描画
	DrawGraph(pos.x, pos.y + height - splitLength, frameGh[6], true);
	DrawExtendGraph(pos.x + splitLength, pos.y + height - splitLength, pos.x + width - splitLength, pos.y + height, frameGh[7], true);
	DrawGraph(pos.x + width - splitLength, pos.y + height - splitLength, frameGh[8], true);
}

//------------GraphicUI作成用データクラス----------------
UIData::UIData(std::string GraphicPass, int AllNum, int WidthNum, int HeightNum, int XSize, int YSize, float PosX, float PosY)
{
	pass = GraphicPass;
	allNum = AllNum;
	widthNum = WidthNum;
	heightNum = HeightNum;
	xSize = XSize;
	ySize = YSize;

	leftTopPos.x = PosX;
	leftTopPos.y = PosY;
}

UIData::~UIData()
{
}


