#pragma once
#include"../../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<memory>

class Resources;
class Graphic;
class GraphicUI;

class EditorManager {


public:

	Resources* resources = nullptr;

	EditorManager();

	float deltatime_;

	void InitManager();

	int mouseX = 0;
	int mouseY = 0;

	//mainシークエンスで選んだグラフィック 位置と大きさを決めるために使う
	Graphic* nowSelectGraphic = nullptr;
	//大きさ変更中のグラフィック
	//std::vector<Graphic*>editGraphic;

	//std::vector<GraphicUI*>editMenu;

	//最終決定位置のグラフィック
	std::vector<GraphicUI*>setGraphic;


	bool CheckMousePointToRect(int MouseX, int MouseY, int RectLeftTopX, int RectWidth, int RectTopY, int RectHeight);

	void Update();
	void Draw();

private:
	GraphicUI* resourcesFrame = nullptr;
	GraphicUI* saveButton = nullptr;
	GraphicUI* resetButton = nullptr;

	Graphic* edit = nullptr;
	GraphicUI* makeMenu = nullptr;

	int editWidth = 48;
	int editHeight = 48;

	int black;

	//初期シークエンスを設定
	tnl::Sequence<EditorManager> main_sequence_ =
		tnl::Sequence<EditorManager>(this, &EditorManager::Seq_main);

	//UI画像を選ぶシークエンス
	bool Seq_main(const float deltatime);
	//UI画像を置くまでのシークエンス
	bool Seq_Place(const float deltatime);
	//UI画像を引き伸ばすシークエンス
	bool Seq_Edit(const float deltatime);


	//シークエンスの列挙体
	enum class SEQUENCE {
		main,
		place,
		edit,
		MAX
	};
	//今のシークエンス
	SEQUENCE nowSeq = SEQUENCE::main;


	std::vector<std::string> UIText;
	//シークエンスを変更する関数
	void ChangeSequence(SEQUENCE seq);
	//現在のシークエンス名を描画する関数
	void DrawNowSeqName(SEQUENCE seq);

	//画面内のUIをリセット、全消去する関数
	void Reset();

	//---------アウトプット用-------------//
	//出力用の文字列型にデータを整形する関数
	void UiToString();
	//出力関数 カンマ区切りのデータで出力
	void UiOutput();


};