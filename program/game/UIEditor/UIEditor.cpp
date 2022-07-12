#include "UIEditor.h"
#include"../UI/GraphicUI.h"
#include"../UIEditor/Graphic.h"
#include"../Manager/GameManager.h"

using namespace std;

UIEditor::UIEditor()
{
	Init();


}

UIEditor::~UIEditor()
{
}

void UIEditor::Init()
{
	//GameManagerインスタンス取得
	gManager = GameManager::Instance();

	//リソースグラフィック欄の背景生成
	{
		auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 0.0f, 0.0f);
		resourcesFrame = new GraphicUI(300, 768, data);
	}
	//出力ボタンの生成
	{
		//auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 900.0f, 0.0f);
		saveButton = new GraphicUI("graphics/UIEditor/SaveButton.png", 950, 100);
	}
	//リセット/全消去ボタンの生成
	{
		//auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 900.0f, 110.0f);
		resetButton = new GraphicUI("graphics/UIEditor/ResetButton.png", 950, 210);
	}
	//ロードボタンの生成
	{
		//auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 900.0f, 220.0f);
		loadButton = new GraphicUI("graphics/UIEditor/LoadButton.png", 950, 320);
	}
	//モード変更ボタンの生成
	{
		//auto data = std::make_shared<UIData>("graphics/ModeNoEdit.png", 9, 3, 3, 16, 16, 900, 330);
		modeChangeButton = new GraphicUI("graphics/UIEditor/ModeNoEdit.png", 950, 430);
	}
}

void UIEditor::Update()
{
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

void UIEditor::LoadResourceGraphic(std::string Pass, int Width, int Height)
{

	auto pos = resources.back()->pos;
	pos.y += 100;

	//リソースを生成する
	auto resource = std::make_shared<Graphic>(tnl::Vector3(150, 100, 0), Pass, Width, Height);
	//配列に格納
	resources.emplace_back(resource);

}

void UIEditor::ReLoadResource()
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
	FindHandle = FileRead_findFirst("graphics\\UI\\*.png", &info);

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

void UIEditor::LoadDefaultResource()
{
	auto black = std::make_shared<Graphic>(tnl::Vector3(150, 100, 0), "graphics/FrameBlack.png", 48, 48);
	auto white = std::make_shared<Graphic>(tnl::Vector3(150, 200, 0), "graphics/FrameWhite.png", 48, 48);

	resources.emplace_back(black);
	resources.emplace_back(white);
}

void UIEditor::DrawResource()
{
	for (auto resource : resources) {
		//DrawRotaGraph(resource->pos.x, resource->pos.y, 1, 0, resource->gh, false);
		//どんな素材画像も100x100に縮小して描画する
		DrawExtendGraph(resource->pos.x - 50, resource->pos.y - 50, resource->pos.x + 50, resource->pos.y + 50, resource->gh, true);
	}
}

//画面に設置するUI画像を左端の画像リストから選ぶシークエンス デフォルト画面
bool UIEditor::SeqSelect(const float DeltaTime)
{
	//ロードボタンを押したときの処理


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

void UIEditor::DrawSelectSequence()
{


	//リソースの表示
	//背景
	resourcesFrame->Draw();
	DrawResource();

	//セーブ、リセット、ロード、モード変更ボタンの表示
	saveButton->Draw();
	resetButton->Draw();
	loadButton->Draw();
	modeChangeButton->Draw();
}

void UIEditor::DrawPlaceSequence()
{
}

void UIEditor::DrawEditSequence()
{
}

void UIEditor::LoadUI(std::string Pass)
{
	auto loadUICsv = tnl::LoadCsv(Pass);

	for (int i = 1; i < loadUICsv.size(); ++i) {


		int allNum = stoi(loadUICsv[i][2]);
		int widthNum = stoi(loadUICsv[i][3]);
		int heightNum = stoi(loadUICsv[i][4]);
		int widthSize = stoi(loadUICsv[i][5]);
		int heightSize = stoi(loadUICsv[i][6]);

		float posX = stof(loadUICsv[i][7]);
		float posY = stof(loadUICsv[i][8]);

		int frameWidth = stoi(loadUICsv[i][9]);
		int frameHeight = stoi(loadUICsv[i][10]);


		//UIDataクラスを生成
		auto data = std::make_shared<UIData>(loadUICsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, posX, posY);

		if (loadUICsv[i][11] == "") {
			//GraphicUIクラスを生成(枠の中に画像がない場合
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data);

			//vectorに登録
			makedUI.emplace_back(newUI);
		}
		else {
			//GraphicUIクラスを生成(枠の中に画像がある場合
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][11], data);

			//vectorに登録
			makedUI.emplace_back(newUI);
		}
	}
}
