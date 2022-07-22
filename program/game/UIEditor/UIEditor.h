#pragma once
#include<string>
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class GraphicUI;
class Graphic;

/*
組み込み型のUIエディターを作る

必要要件

csvから読み込んでUIの生成,描画が出来ること
実行中にビジュアル的にUIの調整が可能で、テキストへの出力が行えること

枠のみ、枠と画像、画像のみが選べること

自由拡大か、等比率拡大か、等倍を選べること

文字の色が変更できること
*/

class UIEditor
{
public:
	UIEditor();
	~UIEditor();

	//初期化関数
	void Init();
	//毎フレーム実行する更新関数
	void Update();
	//毎フレーム描画する関数
	void Draw();

	//CsvからのUIロード関数
	void LoadUI(std::string Pass);

	//リソース画像の再読み込み(実行画面中のボタンに仕込む 普段はこちらでリロードする)
		//指定したフォルダの中の全ての画像を読み込む
	void LoadFileResource();

private:
	//gamemanager
	GameManager* gManager = nullptr;

	int mouseX = 0;
	int mouseY = 0;

	//作成、読み込んだUIの配列
	std::vector<std::shared_ptr<GraphicUI>> makedUI;

	//リソース画像の配列
	std::vector<std::shared_ptr<Graphic>>resources;

	//selectシークエンスで選択した画像リソースポインタ
	std::shared_ptr<Graphic>nowSelectGraphic = nullptr;

	//リソース選択関数
	bool CheckSelectResource();

	//ロード時の拡大ありなし
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//--------------UIの拡大処理関係--------------------//

	//画像の拡大モード
	enum class EDITMODE :uint32_t {
		NOEDIT,		//拡大なし
		SAMERATIO,	//等比率拡大
		FREERATIO,	//自由拡大
		MAX
	};
	//関数使用のための配列
	const EDITMODE MODE[static_cast<uint32_t>(EDITMODE::MAX)] = { EDITMODE::NOEDIT,EDITMODE::SAMERATIO,EDITMODE::FREERATIO };

	//modeごとの使用画像配列
	const std::string MODEGRAPHICPASS[static_cast<uint32_t>(EDITMODE::MAX)] = { "graphics/UIEditor/ModeNoEdit.png","graphics/UIEditor/ModeSameRatio.png","graphics/UIEditor/ModeFreeRatio.png" };

	//現在のモード　フォルトは拡大なし
	int nowMode = static_cast<uint32_t>(EDITMODE::NOEDIT);

	//拡大モードを変更する関数
	inline void ChangeEditMode() {
		//クリックするごとに0->1->2->0->...の順で循環する　
		nowMode = (nowMode + 1) % static_cast<uint32_t>(EDITMODE::MAX);
	}
	//--------------------------------------------------//

	//----------エディター本体のシステムUI----------//

	//左端に置くUI見本の背景フレーム
	//GraphicUI* resourcesFrame = nullptr;
	std::shared_ptr<GraphicUI> resourcesFrame = nullptr;
	//現在のUIをcsvとして出力するボタン
	std::shared_ptr<GraphicUI> saveButton = nullptr;
	//現在の画面のUIを全てリセットするボタン
	std::shared_ptr<GraphicUI> resetButton = nullptr;
	//特定の名前のcsvからUIをロードし表示するボタン
	std::shared_ptr<GraphicUI> loadButton = nullptr;

	//拡大モードの変更ボタン
	std::shared_ptr<GraphicUI> modeChangeButton = nullptr;

	//システムUIのボタン配列
	std::vector<std::shared_ptr<GraphicUI>>SystemButtons;
	//システムUI
	enum class SYSTEMUI :uint32_t {
		SAVE,
		RESET,
		LOAD,
		CHANGE,
		MAX
	};

	//システムUIとのクリック判定関数
	void CheckButtonClick();

	//saveボタン
	void SaveUIButton();
	//resetボタン
	void ResetUIButton();
	//loadボタン
	void LoadUIButton();
	//changeボタン
	void ModeChangeButton();

	//ボタンを押したときの処理を入れておく関数の配列
	const std::function< void(UIEditor*) > BUTTONPROCESS[4] = { &UIEditor::SaveUIButton,&UIEditor::ResetUIButton,
																&UIEditor::LoadUIButton,&UIEditor::ModeChangeButton };

	//---------アウトプット用-------------//
	//出力用整形済み文字列配列
	std::vector<std::string> UIText;

	//出力用の文字列型にデータを整形する関数
	void UiToString();
	//出力関数 カンマ区切りのデータで出力
	void UiOutput();
	//--------------------------------------//


	//----------UIEditorのリソース関係の関数----------//

	//リソース画像の読み込み(パス経由 コードでの暫定的なデバッグに使用)
	void LoadResourceGraphic(std::string Pass, int Width, int Height);

	//debugのためpublicに移動
	/*
	//リソース画像の再読み込み(実行画面中のボタンに仕込む 普段はこちらでリロードする)
	//指定したフォルダの中の全ての画像を読み込む
	void LoadFileResource();
	*/

	//リロード対象
	enum class UIFILE :uint32_t {
		DEFAULT,
		SAVED,
		DEBUG,
		MAX
	};
	//UIロード対象のパス
	const std::string RELOADPASS[static_cast<uint32_t>(UIFILE::MAX)] = { "Csv/UI/SaveUI.csv","Csv/UI/TestSaveUI.csv","Csv/UI/TestSaveUI.csv" };

	//指定フォルダの相対パス(slnファイルが有る場所からのパス)
	const std::string LOADFILEPASS = "graphics\\UI\\*.png";

	//リソースエリアに描画する画像の正方サイズ
	const int DRAWSIZE = 100;

	//初回リソース画像読み込み(基本UIの枠のみ必ず読み込む)
	void LoadDefaultResource();

	//リソース画像の描画
	void DrawResource();

	//----------------------------------------------//

	//----------シークエンス処理---------------------//
	//初期シークエンスを設定
	tnl::Sequence<UIEditor> mainSequence =
		tnl::Sequence<UIEditor>(this, &UIEditor::SeqSelect);

	//各シークエンスのUpdate関数
	bool SeqSelect(const float DeltaTime);
	bool SeqPlace(const float DeltaTime);
	bool SeqEdit(const float DeltaTime);

	//シークエンス一覧
	enum class SEQUENCE :uint32_t {
		SELECT,
		PLACE,
		EDIT,
		MAX
	};

	SEQUENCE nowSequence = SEQUENCE::SELECT;

	//シークエンス変更関数
	bool ChangeSequence(SEQUENCE NextSeq);

	//シークエンスごとの描画関数
	void DrawSelectSequence();
	void DrawPlaceSequence();
	void DrawEditSequence();

	//現在のシークエンスの描画関数
	const std::function< void(UIEditor*) > DRAWSEQUENCE[3] = { &UIEditor::DrawSelectSequence,&UIEditor::DrawPlaceSequence,&UIEditor::DrawEditSequence };


};

