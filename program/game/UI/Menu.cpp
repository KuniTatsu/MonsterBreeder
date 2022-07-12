#include "Menu.h"
#include"../Manager/GameManager.h"

Menu::Menu(int MenuTopX, int MenuTopY, int Width, int Height, std::string GhPath)
{
	gManager = GameManager::Instance();


	menuTopPos = tnl::Vector3(MenuTopX, MenuTopY, 0);

	width = Width;
	height = Height;
	menuBackGroundGhPass = GhPath;

	gManager->LoadDivGraphEx(GhPath, 9, 3, 3, 16, 16, menuBackGroundGh);


}

void Menu::MenuDraw()
{
	//上段
	DrawGraph(menuTopPos.x, menuTopPos.y, menuBackGroundGh[0], true);
	DrawExtendGraph(menuTopPos.x + 16, menuTopPos.y, menuTopPos.x + width - 16, menuTopPos.y + 16, menuBackGroundGh[1], true);
	DrawGraph(menuTopPos.x + width - 16, menuTopPos.y, menuBackGroundGh[2], true);

	//中段
	DrawExtendGraph(menuTopPos.x, menuTopPos.y + 16, menuTopPos.x + 16, menuTopPos.y + height - 16, menuBackGroundGh[3], true);
	DrawExtendGraph(menuTopPos.x + 16, menuTopPos.y + 16, menuTopPos.x + width - 16, menuTopPos.y + height - 16, menuBackGroundGh[4], true);
	DrawExtendGraph(menuTopPos.x + width - 16, menuTopPos.y + 16, menuTopPos.x + width, menuTopPos.y + height - 16, menuBackGroundGh[5], true);

	//下段
	DrawGraph(menuTopPos.x, menuTopPos.y + height - 16, menuBackGroundGh[6], true);
	DrawExtendGraph(menuTopPos.x + 16, menuTopPos.y + height - 16, menuTopPos.x + width - 16, menuTopPos.y + height, menuBackGroundGh[7], true);
	DrawGraph(menuTopPos.x + width - 16, menuTopPos.y + height - 16, menuBackGroundGh[8], true);
}

SelectMenu::SelectMenu(int TopX, int TopY, int Width, int Height, std::string GhPath)
	: Menu(TopX, TopY, Width, Height, GhPath)//メニューの大きさを決める(開始座標:左上,横幅,縦幅)
{
	highLightGh = gManager->LoadGraphEx("graphics/MenuHighLight.png");


}

SelectMenu::~SelectMenu()
{
}

void SelectMenu::AddMenuElements(std::string Text)
{
	//まだメニュー項目がなければMenuの枠から半分だけずらして生成する→中心座標にする
	if (elements.empty()) {
		auto element = std::make_unique<Element>(menuTopPos.x + (width / 2), menuTopPos.y + 10, Text);
		elements.emplace_back(std::move(element));
		return;
	}
	//メニューが生成されていれば、末尾の項目のy座標からオフセット分だけずらして生成する
	auto element = std::make_unique<Element>(menuTopPos.x + (width / 2), elements.back()->centerPos.y + 25, Text);
	elements.emplace_back(std::move(element));


}

bool SelectMenu::MenuUpdate()
{
	//メニューの選択中項目の移動
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		nowSelectNum = (nowSelectNum + (elements.size() - 1)) % elements.size();
		//tnl::DebugTrace("\n[%d]番メニュー選択中\n", nowSelectNum);
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		nowSelectNum = (nowSelectNum + 1) % elements.size();
		//tnl::DebugTrace("\n[%d]番メニュー選択中\n", nowSelectNum);
	}


	return false;
}

bool SelectMenu::CheckMenuClick()
{
	for (int i = 0; i < elements.size(); ++i) {
		if (elements[i]->isClickElement()) {
			nowSelectNum = i;
			return true;
		}
	}

	return false;
}



void SelectMenu::DrawSelectMenu()
{
	//背景の描画
	MenuDraw();

	//メニュー項目の描画
	for (int i = 0; i < elements.size(); ++i) {
		elements[i]->DrawElement();
	}

	//--------------選択中項目のハイライト---------------------//
	//アルファ合成に変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//描画領域の指定
	//SetDrawArea(menuTopPos.x, menuTopPos.y, menuTopPos.x + width, menuTopPos.y + height);

	//ハイライト画像の描画
	DrawRotaGraph(elements[nowSelectNum]->centerPos.x, elements[nowSelectNum]->centerPos.y, 1, 0, highLightGh, false);

	//SetDrawArea(0, 0, 1024, 768);
	//ブレンドモードを戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}



//--------------Menu項目,背景画像,当たり判定用クラス--------------//
Element::Element(float CenterX, float CenterY, std::string Text)
{
	gManager = GameManager::Instance();

	centerPos.x = CenterX;
	centerPos.y = CenterY + 10;

	leftPos.x = CenterX - TEXTRECT.x / 2;
	leftPos.y = CenterY - TEXTRECT.y / 2;

	element = Text;

	gh = gManager->LoadGraphEx("graphics/MenuRect.png");
}

Element::~Element()
{
}

bool Element::isClickElement()
{
	if (gManager->isClickedRect(gManager->mousePosX, gManager->mousePosY, leftPos.x, leftPos.y, leftPos.x + TEXTRECT.x, leftPos.y + TEXTRECT.y))
	{
		return true;
	}
	return false;
}

void Element::DrawElement()
{
	DrawRotaGraph(centerPos.x, centerPos.y, 1, 0, gh, false);

	DrawStringEx(leftPos.x + 10, centerPos.y-10, -1, element.c_str());
}
