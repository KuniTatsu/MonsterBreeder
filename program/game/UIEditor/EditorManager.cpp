/*
#include "EditorManager.h"
#include "../support/Support.h"
#include"DxLib.h"
#include"Resources.h"
#include"Graphic.h"
#include"MenuWindow.h"
#include<fstream>
#include<string>

EditorManager::EditorManager()
{
}

void EditorManager::InitManager()
{
	resourcesFrame = new Menu(0, 0, 300, 768, "graphics/WindowBase_02.png");
	saveButton = new Menu(900, 0, 100, 100, "graphics/WindowBase_02.png");
	resetButton = new Menu(900, 110, 100, 100, "graphics/WindowBase_02.png");

	black = GetColor(0, 0, 0);
	resources = new Resources();
}

bool EditorManager::CheckMousePointToRect(int MouseX, int MouseY, int RectLeftTopX, int RectWidth, int RectTopY, int RectHeight)
{
	if (MouseX >= RectLeftTopX && MouseX <= RectLeftTopX + RectWidth
		&& MouseY >= RectTopY && MouseY <= RectTopY + RectHeight) {
		return true;
	}
	return false;
}

void EditorManager::Update()
{
	main_sequence_.update(deltatime_);
	GetMousePoint(&mouseX, &mouseY);
	resources->Update();
}

void EditorManager::Draw()
{
	if (nowSeq == sequence::main) {
		saveButton->Menu_Draw();
		DrawStringEx(saveButton->menu_x + 10, saveButton->menu_y + 50, black, "save");

		resetButton->Menu_Draw();
		DrawStringEx(resetButton->menu_x + 10, resetButton->menu_y + 50, black, "reset");

		DrawNowSeqName(nowSeq);

	}
	//if (setGraphic.empty())return;
	for (auto set : setGraphic) {
		set->Menu_Draw();
	}
	if (nowSeq == sequence::place) {
		DrawRotaGraph(mouseX, mouseY, 1, 0, nowSelectGraphic->gh, true);
	}
	if (nowSeq == sequence::edit) {
		if (makeMenu == nullptr)return;
		makeMenu->Menu_Draw();
	}

	if (nowSeq == sequence::main) {
		if (CheckMousePointToRect(mouseX, mouseY, resourcesFrame->menu_x,
			resourcesFrame->menu_width, resourcesFrame->menu_y, resourcesFrame->menu_height)) {

			resourcesFrame->Menu_Draw();
			for (auto g : resources->gObject) {
				DrawRotaGraph(g->pos.x, g->pos.y, 1, 0, g->gh, true);
			}
		}
		else {
			DrawBox(0, 0, 200, 50, -1, true);
			DrawStringEx(0, 25, black, "resources");
		}
	}
}

bool EditorManager::Seq_main(const float deltatime)
{
	for (auto g : resources->gObject) {
		if (t2k::Input::isMouseTrigger(t2k::Input::MOUSE_RELEASED_LEFT)) {
			if (CheckMousePointToRect(mouseX, mouseY, g->pos.x - (g->width / 2), g->width, g->pos.y - (g->height / 2), g->height)) {
				nowSelectGraphic = g;
				ChangeSequence(sequence::place);
				return true;
			}
		}
	}

	if (t2k::Input::isMouseTrigger(t2k::Input::MOUSE_RELEASED_LEFT)) {
		if (CheckMousePointToRect(mouseX, mouseY, saveButton->menu_x,
			saveButton->menu_width, saveButton->menu_y, saveButton->menu_height)) {
			//テキストに書き出す
			UiToString();
			UiOutput();
		}
		if (CheckMousePointToRect(mouseX, mouseY, resetButton->menu_x,
			resetButton->menu_width, resetButton->menu_y, resetButton->menu_height)) {
			Reset();
		}
	}

	return true;
}

bool EditorManager::Seq_Place(const float deltatime)
{
	//クリックしたら
	if (t2k::Input::isMouseTrigger(t2k::Input::MOUSE_RELEASED_LEFT)) {

		Graphic* newGraphic = new Graphic(t2k::Vector3(mouseX, mouseY, 0), nowSelectGraphic->gh, nowSelectGraphic->width, nowSelectGraphic->height);

		edit = newGraphic;
		ChangeSequence(sequence::edit);
	}

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		ChangeSequence(sequence::main);
		return true;
	}
	return true;
}
bool EditorManager::Seq_Edit(const float deltatime)
{
	if (main_sequence_.isStart()) {
		std::string Url = resources->GetURL(edit->gh);

		Menu* menu = new Menu(mouseX - (edit->width / 2), mouseY - (edit->height / 2), editWidth, editHeight, Url);
		makeMenu = menu;
	}
	makeMenu->menu_width = mouseX - makeMenu->menu_x;
	makeMenu->menu_height = mouseY - makeMenu->menu_y;

	//makeMenu->Menu_Draw();

	if (t2k::Input::isMouseTrigger(t2k::Input::MOUSE_RELEASED_LEFT)) {

		setGraphic.emplace_back(makeMenu);

		ChangeSequence(sequence::main);
		return true;
	}
	return true;
}
void EditorManager::ChangeSequence(sequence seq)
{
	nowSeq = seq;
	if (seq == sequence::main) {
		main_sequence_.change(&EditorManager::Seq_main);
	}
	else if (seq == sequence::place) {
		main_sequence_.change(&EditorManager::Seq_Place);
	}
	else if (seq == sequence::edit) {
		main_sequence_.change(&EditorManager::Seq_Edit);
	}


}

void EditorManager::DrawNowSeqName(sequence seq)
{
	if (seq == sequence::main) {
		DrawStringEx(0, 700, -1, "MainSequence");
	}
	else if (seq == sequence::place) {
		DrawStringEx(0, 700, -1, "PlaceSequence");
	}
	else if (seq == sequence::edit) {
		DrawStringEx(0, 700, -1, "EditSequence");
	}
}

void EditorManager::Reset()
{
	setGraphic.clear();
	t2k::debugTrace("\n完成UIリストを全削除しました\n");
}

void EditorManager::UiToString()
{
	for (auto menu : setGraphic) {

		std::string hoge = "Menu* hoge=new Menu(" + std::to_string(menu->menu_x) + "," + std::to_string(menu->menu_y) + "," + std::to_string(menu->menu_width) + "," +
			std::to_string(menu->menu_height) + "," + "gh(int)" + ")";
		UIText.emplace_back(hoge);
	}
}

void EditorManager::UiOutput()
{
	std::ofstream writingfile;
	std::string filename = "OutPut/newUI.txt";

	writingfile.open(filename, std::ios::out);
	int i = 0;
	for (auto outText : UIText) {
		//std::string writingtext = UIText[i];
		writingfile << outText << std::endl;
		++i;
	}

	writingfile.close();

}
*/