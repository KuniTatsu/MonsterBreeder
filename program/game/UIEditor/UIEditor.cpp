#include "UIEditor.h"
#include<fstream>
#include"../UI/GraphicUI.h"
#include"../UIEditor/Graphic.h"
#include"../Manager/GameManager.h"

using namespace std;

UIEditor::UIEditor()
{
}

UIEditor::~UIEditor()
{
}
//エディターの初期化関数
void UIEditor::Init()
{
	//GameManagerインスタンス取得
	gManager = GameManager::Instance();

	LoadDefaultResource();

	//リソースグラフィック欄の背景生成
	{
		auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 0.0f, 0.0f);
		resourcesFrame = std::make_shared<GraphicUI>(300, 768, data, static_cast<uint32_t>(LOADMODE::NORMAL));
	}
	//出力ボタンの生成
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/SaveButton.png", 1, 1, 1, 100, 100, 900.0f, 0.0f);
		saveButton = std::make_shared<GraphicUI>("graphics/UIEditor/SaveButton.png", 100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(saveButton);
	}
	//リセット/全消去ボタンの生成
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/ResetButton.png", 1, 1, 1, 100, 100, 900.0f, 110.0f);
		resetButton = std::make_shared<GraphicUI>("graphics/UIEditor/ResetButton.png", 100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(resetButton);
	}
	//ロードボタンの生成
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/LoadButton.png", 1, 1, 1, 100, 100, 900.0f, 220.0f);
		loadButton = std::make_shared<GraphicUI>("graphics/UIEditor/LoadButton.png", 100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(loadButton);
	}
	//モード変更ボタンの生成
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/ModeNoEdit.png", 1, 1, 1, 100, 100, 900.0f, 330.0f);
		modeChangeButton = std::make_shared<GraphicUI>("graphics/UIEditor/ModeNoEdit.png", 100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(modeChangeButton);
	}
}

void UIEditor::Update()
{
	//マウスポジション取得
	GetMousePoint(&mouseX, &mouseY);
	//現在のシークエンスの更新関数の実行
	mainSequence.update(gManager->deltatime);
}

void UIEditor::Draw()
{
	//保存されたUIの描画
	for (auto ui : makedUI) {
		ui->Draw();
	}

	//現在のシークエンスの間のみ描画したい内容の描画
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);

	
}
void UIEditor::CheckButtonClick()
{
	//マウスが右側のエリアになかったらそもそも判定しない
	if (mouseX < 700)return;

	for (int i = 0; i < SystemButtons.size(); ++i) {

		//ボタンの左上の座標を取得
		tnl::Vector3 leftTopPos = SystemButtons[i]->GetLeftTopPos();
		//もしボタンがクリックされていたら
		if (gManager->isClickedRect(mouseX, mouseY, leftTopPos.x, leftTopPos.y,
			leftTopPos.x + SystemButtons[i]->GetUIWidth(), leftTopPos.y + SystemButtons[i]->GetUIHeight()))
		{
			BUTTONPROCESS[i](this);
			break;
		}
	}
}
//セーブボタンを押したときの処理
void UIEditor::SaveUIButton()
{
	tnl::DebugTrace("\nセーブボタンが押されたよ\n");
	//カンマ区切りのテキストデータに変換
	UiToString();
	//指定したパスにCsvファイルを生成or上書き
	UiOutput();
}
//リセットボタンの処理
void UIEditor::ResetUIButton()
{
	//画面の中にあるUIを全て消去する
	makedUI.clear();
}
//ロードボタンの処理
void UIEditor::LoadUIButton()
{
	//標準の読み込みパスでUIをロードする
	LoadUI(RELOADPASS[static_cast<uint32_t>(UIFILE::DEFAULT)]);
}
//チェンジボタンの処理
void UIEditor::ModeChangeButton()
{
	//拡大モードを一つ進める
	ChangeEditMode();
	//画像を変更
	modeChangeButton->ReLoadGraphic(MODEGRAPHICPASS[nowMode]);

}
//UIをCSV出力する際のカンマ区切りデータの文字列に変換する関数
void UIEditor::UiToString()
{
	int idCount = 0;
	for (auto ui : makedUI) {

		std::string data = ui->GetCsvStringData(idCount);

		UIText.emplace_back(data);
		idCount++;
	}
}
//Csvデータの出力関数
void UIEditor::UiOutput()
{
	//ofstream型の変数 開いたファイルが展開される
	std::ofstream writingfile;
	//相対パス
	//std::string filename = "Csv/UI/TestSaveUI.csv";
	std::string filename = RELOADPASS[static_cast<uint32_t>(UIFILE::DEBUG)];

	//パスから出力設定でファイルを開く
	writingfile.open(filename, std::ios::out);

	//0行目だけは先に書き込む
	writingfile << "id, frameGhPass, type 0:split, 1 : normal, allNum, widthNum, heightNum, widthSize, heightSize, leftTopPos.x, leftTopPos.y, FrameWidth, FrameHeight, ingraphicsPass" << std::endl;


	//UITextにある内容を全てcsvファイルに書き込む
	for (auto outText : UIText) {
		writingfile << outText << std::endl;
	}
	//開いたファイルの開放
	writingfile.close();
}
//画像パスから新しい画像リソースをロードする
void UIEditor::LoadResourceGraphic(std::string Pass, int Width, int Height)
{

	auto pos = resources.back()->pos;
	pos.y += 100;

	//リソースを生成する
	auto resource = std::make_shared<Graphic>(tnl::Vector3(150, 100, 0), Pass, Width, Height);
	//配列に格納
	resources.emplace_back(resource);

}
//特定のフォルダの中にある特定の拡張子の画像を読み込む
void UIEditor::LoadFileResource()
{
	//リソースの配列を空にする
	resources.clear();

	//構造体 info.Nameでファイル名が取得できる
	FILEINFO info;

	//ファイルがあるかどうかのフラグ
	DWORD_PTR FindHandle;

	//検索開始　フォルダ内の最初のファイルの情報を取得
	//フォルダ内の.png形式の画像のみを検索する
	//第一引数にフォルダの実行ファイルからの相対パスを入れる
	FindHandle = FileRead_findFirst(LOADFILEPASS.c_str(), &info);

	//もし最初のファイルが見つかったら走る処理
	if (FindHandle != (DWORD_PTR)-1)
	{
		//無限ループ処理
		while (1) {
			////次のファイルを検索。無かったらループを抜けて終了
			//if (FileRead_findNext(FindHandle, &info) < 0)break;

			//ファイル名を取得
			std::string name = info.Name;

			//画像をロード
			int gh = gManager->LoadGraphEx("graphics/UI/" + name);

			//もしリソースの配列が空だったら初期ポジションで生成する
			if (resources.empty()) {
				//リソースを生成する
				auto resource = std::make_shared<Graphic>(tnl::Vector3(70, 70, 0), gh);
				//配列に格納
				resources.emplace_back(resource);

				//次のファイルを検索。無かったらループを抜けて終了
				if (FileRead_findNext(FindHandle, &info) < 0)break;
				continue;
			}
			else {
				//一つ前のリソースの描画座標を取得する
				auto pos = resources.back()->pos;
				//画像同士の間隔
				pos.y += 110;

				//リソースを生成する
				auto resource = std::make_shared<Graphic>(pos, gh);
				//配列に格納
				resources.emplace_back(resource);
			}
			//次のファイルを検索。無かったらループを抜けて終了
			if (FileRead_findNext(FindHandle, &info) < 0)break;
		}
		//検索ハンドルの消去
		FileRead_findClose(FindHandle);
	}
}
bool UIEditor::CheckSelectResource()
{
	//マウスが左側にいなければそもそも判定しない
	if (mouseX > 300)return false;
	//int hoge = 0;
	//if (hoge == 0) {
	//	hoge++;
	//}

	for (auto graphic : resources) {
		//左クリック検知
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
			//左上座標
			int topLeftX = graphic->pos.x - DRAWSIZE / 2;
			int topLeftY = graphic->pos.y - DRAWSIZE / 2;

			//右下座標
			int bottomRightX = graphic->pos.x + DRAWSIZE / 2;
			int bottomRightY = graphic->pos.y + DRAWSIZE / 2;

			//リソース画像をクリックしていたら
			//if (gManager->isClickedRect(mouseX, mouseY, topLeftX, topLeftY, bottomRightX, bottomRightY)) {
			if (gManager->isClickedRect(mouseX, mouseY, topLeftX, topLeftY, bottomRightX, bottomRightY)) {
				//選択中の画像にポインタをいれる
				nowSelectGraphic = graphic;
				//設置シークエンスに移動する
				//ChangeSequence(SEQUENCE::PLACE);

				//trueが帰れば設置シークエンスに移動させる
				return true;
			}
		}
	}
	//falseが帰るとシークエンスを移動しない
	return false;
}
//初回にロードする分割引き伸ばしのデフォルトUI
void UIEditor::LoadDefaultResource()
{
	auto black = std::make_shared<Graphic>(tnl::Vector3(150, 100, 0), "graphics/FrameBlack.png", 48, 48);
	auto white = std::make_shared<Graphic>(tnl::Vector3(150, 200, 0), "graphics/FrameWhite.png", 48, 48);

	resources.emplace_back(black);
	resources.emplace_back(white);
}
//画面左端に描画する素材画像
void UIEditor::DrawResource()
{
	for (auto resource : resources) {
		//DrawRotaGraph(resource->pos.x, resource->pos.y, 1, 0, resource->gh, false);
		//どんな素材画像も100x100に縮小して描画する
		DrawExtendGraph(resource->pos.x - DRAWSIZE / 2, resource->pos.y - DRAWSIZE / 2,
			resource->pos.x + DRAWSIZE / 2, resource->pos.y + DRAWSIZE / 2, resource->gh, true);
	}
}

//画面に設置するUI画像を左端の画像リストから選ぶシークエンス デフォルト画面
bool UIEditor::SeqSelect(const float DeltaTime)
{
	//セーブなどのボタンクリック検知
	CheckButtonClick();

	//リソースエリアから画像を選ぶ 
	//trueが帰ってくれば画像を選んでいるので、設置シークエンスに移動する
	if (CheckSelectResource())ChangeSequence(SEQUENCE::PLACE);


	return true;
}
//Selectシークエンスで選んだUI画像を置く場所を決めるシークエンス 大きさ変更を行わない場合はSelectに戻る
bool UIEditor::SeqPlace(const float DeltaTime)
{



	return true;
}
//Placeシークエンスで置いたUIの右下を引き伸ばし、大きさ変更を行うシークエンス
bool UIEditor::SeqEdit(const float DeltaTime)
{
	return true;
}

//シークエンス変更関数
bool UIEditor::ChangeSequence(SEQUENCE NextSeq)
{
	switch (NextSeq)
	{
	case SEQUENCE::SELECT:
		mainSequence.change(&UIEditor::SeqSelect);
		nowSequence = SEQUENCE::SELECT;
		return true;
		break;
	case SEQUENCE::PLACE:
		mainSequence.change(&UIEditor::SeqPlace);
		nowSequence = SEQUENCE::PLACE;
		return true;
		break;
	case SEQUENCE::EDIT:
		mainSequence.change(&UIEditor::SeqEdit);
		nowSequence = SEQUENCE::EDIT;
		return true;
		break;
	default:
		return false;
		break;
	}

	return false;
}

void UIEditor::DrawSelectSequence()
{
	//リソースの表示
	//背景
	resourcesFrame->Draw();
	DrawResource();

	//セーブ、リセット、ロード、モード変更ボタンの表示
	for (auto& button : SystemButtons) {
		button->Draw();
	}
}

void UIEditor::DrawPlaceSequence()
{
	//マウスに選択中の画像を追従させる
	DrawRotaGraph(mouseX, mouseY, 1, 0, nowSelectGraphic->gh, true);
}

void UIEditor::DrawEditSequence()
{
}
//CsvデータからUIをロードする関数 データの並び順を合わせること
void UIEditor::LoadUI(std::string Pass)
{
	//画面内の全てのUIを消去する
	makedUI.clear();

	//CSV読み込み
	auto loadUICsv = tnl::LoadCsv(Pass);

	//1行目からスタート(0行目は項目名)
	for (int i = 1; i < loadUICsv.size(); ++i) {

		//id	frameGhPass	type 0:split,1:normal	allNum	widthNum	heightNum	widthSize	heightSize	leftTopPos.x	leftTopPos.y	FrameWidth	FrameHeight	ingraphicsPass

		//------string型のデータをint型とfloat型に変換し、ローカル変数に保管する処理----//
		//type 0:分割ロード,1:そのままロード
		int type = stoi(loadUICsv[i][2]);

		int allNum = stoi(loadUICsv[i][3]);
		int widthNum = stoi(loadUICsv[i][4]);
		int heightNum = stoi(loadUICsv[i][5]);
		int widthSize = stoi(loadUICsv[i][6]);
		int heightSize = stoi(loadUICsv[i][7]);

		float posX = stof(loadUICsv[i][8]);
		float posY = stof(loadUICsv[i][9]);

		int frameWidth = stoi(loadUICsv[i][10]);
		int frameHeight = stoi(loadUICsv[i][11]);

		//------------------------------------------------------------------------------//

		//UIDataクラスを生成
		auto data = std::make_shared<UIData>(loadUICsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, posX, posY);

		//画像を引き伸ばさずに使うUIの場合
		if (type == static_cast<uint32_t>(LOADMODE::NORMAL)) {

			//GraphicUIクラスを生成(画像を拡大せずに使う場合)
			auto newUI = std::make_shared<GraphicUI>(loadUICsv[i][1], frameWidth, frameHeight, data, type);
			//vectorに登録
			makedUI.emplace_back(newUI);
			//次のループへ
			continue;
		}
		if (loadUICsv[i][12] == "none") {
			//GraphicUIクラスを生成(枠の中に画像がない場合)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);

			//vectorに登録
			makedUI.emplace_back(newUI);
		}
		else {
			//GraphicUIクラスを生成(枠の中に画像がある場合
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][12], data, type);

			//vectorに登録
			makedUI.emplace_back(newUI);
		}
	}
}
