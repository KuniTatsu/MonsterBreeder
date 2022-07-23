#pragma once
//---------------�g����-------------
//�EGameManager�Ȃǂ̏ꏊ��UIEditor�𐶐����Ă��������B
// 
//�EUIEditor�͏�����Ԃł͓����Ȃ��悤�ɂȂ��Ă��܂��B
//	ChangeEnable()�֐��ŗL���ɂ���Ɖ�ʂ��\������܂��B
// 
//�EUI��CSV����̃��[�h����ۂ̃p�X�� RELOADPASS ��ύX���Ă�������
//  �f�t�H���g�ł�sln�t�@�C�����L��K�w���� CSV/UI/ �̒���csv�t�@�C����u���܂�
//�E�t�H���_���̉摜���ꊇ�œǂݍ���Ń��\�[�X�ɓ����p�X�� LOADFILEPASS ��ύX���ĉ����� 
//  �f�t�H���g�ł� graphics\\UI\\*.png ->sln�t�@�C��������K�w����graphics/UI/�̒��ɂ���".png"�摜�̂ݑΏۂɂ��Ă��܂��B
// 
//�EReLoad �`�{�^�����N���b�N�����Load�{�^�������������ɓǂݍ���csv�t�@�C����ύX�ł��܂��B
//�EChange�{�^�����N���b�N�����UI�쐬���̊g����@��ύX�ł��܂�

//�E����Editor���g���ɂ͈ȉ��̃N���X�Ɗ֐��A�ϐ����K�v�ɂȂ�܂��B
//�EGameManager->isClickedRect()	:�Z�`�ƃ}�E�X�̃N���b�N���m�֐�
//�EGameManager->LoadGraphEx()		:std::unorderedmap�𗘗p�����摜�ǂݍ��݊֐�
//�EGameManager->deltatime			:�t���[���b game_main���擾
//�EGraphicUI�N���X					:���ۂɉ�ʓ��ɕ`�悷��UI�̃N���X �����i
//�EUIData�N���X					:GraphicUI�N���X����邽�߂̃f�[�^�N���X ���ɒm��Ȃ��Ă��ǂ�
//�EGraphic�N���X					:Editor���Ŏg�p����f�[�^�N���X ���\�[�X�摜�̕`��ɂ��g�p
//�Edxlib_ext/dxlib_ext.h			:�搶���쐬�������C�u�������g�p���邽�߂̃w�b�_�[
//�E���̑�C++�̃X�^���_�[�h���C�u����:string,vector,memory
//�E�G�f�B�^�{�̂̂��߂̉摜�t�H���_���K�v�ƂȂ�܂��B
//�Egraphics/UIEditor �̒��ɂ���摜�̖��O�͕ύX���Ȃ��ł�������

//�G�f�B�^�[���̊֐��y�ѕϐ��A�萔�͏�L RELOADPASS,LOADFILEPASS�������ύX���Ȃ��ł��������B�����ۏ؂ł��܂���B
//�Ȃɂ��s���_��g�����Ăق����v�f������΋C�y��GP21 �����܂ő��k���������B��ؐ搶�o�R�̕����A�|�����₷����������܂���B


#include<string>
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class GraphicUI;
class Graphic;

/*
�g�ݍ��݌^��UI�G�f�B�^�[�����

�K�v�v��

csv����ǂݍ����UI�̐���,�`�悪�o���邱��

���s���Ƀr�W���A���I��UI�̒������\�ŁA�e�L�X�g�ւ̏o�͂��s���邱��

���R�g�傩�A���䗦�g�傩�A���{��I�ׂ邱��

*/

class UIEditor
{
public:
	UIEditor();
	~UIEditor();

	//�������֐�
	void Init();
	//���t���[�����s����X�V�֐�
	void Update();
	//���t���[���`�悷��֐�
	void Draw();

	//UIEditor�̗L��������Ԃ�؂�ւ���֐�
	void ChangeEnable();

private:
	//gamemanager
	GameManager* gManager = nullptr;

	//UIEditor��\���A�N�����Ă��邩�ǂ���
	bool isEnable = false;

	//�}�E�X���W
	int mouseX = 0;
	int mouseY = 0;

	//�쐬�A�ǂݍ���UI�̔z��
	std::vector<std::shared_ptr<GraphicUI>> makedUI;

	//���\�[�X�摜�̔z��
	std::vector<std::shared_ptr<Graphic>>resources;

	//select�V�[�N�G���X�őI�������摜���\�[�X�|�C���^
	std::shared_ptr<Graphic>nowSelectGraphic = nullptr;

	//edit�V�[�N�G���X�Ŏg�p���邽�߂̉摜���\�[�X�|�C���^
	std::shared_ptr<GraphicUI>edit = nullptr;

	//edit�V�[�N�G���X�Ŏg�p����摜�̍���̊���W
	tnl::Vector3 leftTop = {};

	//���\�[�X�I���֐�
	bool CheckSelectResource();

	//���[�h���̊g�傠��Ȃ�
	enum class LOADMODE :uint32_t {
		SPLIT,
		NORMAL,
		MAX
	};

	//--------------UI�̊g�又���֌W--------------------//

	//�摜�̊g�僂�[�h
	enum class EDITMODE :uint32_t {
		NOEDIT,		//�g��Ȃ�
		SAMERATIO,	//���䗦�g��
		FREERATIO,	//���R�g��
		MAX
	};
	//�֐��g�p�̂��߂̔z��
	const EDITMODE MODE[static_cast<uint32_t>(EDITMODE::MAX)] = { EDITMODE::NOEDIT,EDITMODE::SAMERATIO,EDITMODE::FREERATIO };
	const std::string MODESTRING[static_cast<uint32_t>(EDITMODE::MAX)] = { "NOEDIT","SAME","FREE" };

	//mode���Ƃ̎g�p�摜�z��
	const std::string MODEGRAPHICPASS[static_cast<uint32_t>(EDITMODE::MAX)] = { "graphics/UIEditor/ModeNoEdit.png","graphics/UIEditor/ModeSameRatio.png","graphics/UIEditor/ModeFreeRatio.png" };

	//���݂̃��[�h�@�t�H���g�͊g��Ȃ�
	int nowMode = static_cast<uint32_t>(EDITMODE::NOEDIT);

	//�g�僂�[�h��ύX����֐�
	inline void ChangeEditMode() {
		//�N���b�N���邲�Ƃ�0->1->2->0->...�̏��ŏz����@
		nowMode = (nowMode + 1) % static_cast<uint32_t>(EDITMODE::MAX);
	}

	//edit�V�[�N�G���X�p ���R�g��֐� ���t���[���Ă�
	void EditFreeScale();
	//edit�V�[�N�G���X�p ���䗦�g��֐� ���t���[���Ă�
	void EditSameScale();

	//--------------------------------------------------//

	//----------�G�f�B�^�[�{�̂̃V�X�e��UI----------//

	//���[�ɒu��UI���{�̔w�i�t���[��
	//GraphicUI* resourcesFrame = nullptr;
	std::shared_ptr<GraphicUI> resourcesFrame = nullptr;

	//���݂�UI��csv�Ƃ��ďo�͂���{�^��
	std::shared_ptr<GraphicUI> saveButton = nullptr;
	//���݂̉�ʂ�UI��S�ă��Z�b�g����{�^��
	std::shared_ptr<GraphicUI> resetButton = nullptr;
	//����̖��O��csv����UI�����[�h���\������{�^��
	std::shared_ptr<GraphicUI> loadButton = nullptr;
	//����̃t�H���_���烊�\�[�X�����[�h����{�^��
	std::shared_ptr<GraphicUI> resourceButton = nullptr;

	//�g�僂�[�h�̕ύX�{�^��
	std::shared_ptr<GraphicUI> modeChangeButton = nullptr;

	//�����[�h����CSV��ύX����{�^��
	std::shared_ptr<GraphicUI>reloadChangeButton = nullptr;



	//�V�X�e��UI�̃{�^���z��
	std::vector<std::shared_ptr<GraphicUI>>SystemButtons;
	//�V�X�e��UI
	enum class SYSTEMUI :uint32_t {
		SAVE,
		RESET,
		LOAD,
		CHANGELOAD,
		CHANGE,
		RESOURCE,
		MAX
	};

	//�V�X�e��UI�Ƃ̃N���b�N����֐�
	void CheckButtonClick();

	//save�{�^��
	void SaveUIButton();
	//reset�{�^��
	void ResetUIButton();
	//load�{�^��
	void LoadUIButton();
	//load��ύX�{�^��
	void ChangeLoadCSV();

	//change�{�^��
	void ModeChangeButton();
	//resource�{�^��
	void ResourceButton();

	//�{�^�����������Ƃ��̏��������Ă����֐��̔z��
	const std::function< void(UIEditor*) > BUTTONPROCESS[static_cast<uint32_t>(SYSTEMUI::MAX)] = { &UIEditor::SaveUIButton,&UIEditor::ResetUIButton,
																									&UIEditor::LoadUIButton,& UIEditor::ChangeLoadCSV,
																									&UIEditor::ModeChangeButton,&UIEditor::ResourceButton };

	//---------�A�E�g�v�b�g�p-------------//
	//�o�͗p���`�ςݕ�����z��
	std::vector<std::string> UIText;

	//�o�͗p�̕�����^�Ƀf�[�^�𐮌`����֐�
	void UiToString();
	//�o�͊֐� �J���}��؂�̃f�[�^�ŏo��
	void UiOutput();
	//--------------------------------------//


	//----------UIEditor�̃��\�[�X�֌W�̊֐�----------//

	//�����[�h�Ώ�
	enum class UIFILE :uint32_t {
		DEFAULT,
		SAVED,
		DEBUG,
		MAX
	};

	//mode���Ƃ̎g�p�摜�z��
	const std::string LOADGRAPHICPASS[static_cast<uint32_t>(UIFILE::MAX)] = { "graphics/UIEditor/ReloadDefault.png","graphics/UIEditor/ReloadSaved.png","graphics/UIEditor/ReloadDebug.png" };

	//****************-------------------------���������͂������Ă��ǂ�--------------------------------------------------************//
	//UI���[�h�Ώۂ̃p�X
	const std::string RELOADPASS[static_cast<uint32_t>(UIFILE::MAX)] = { "Csv/UI/SaveUI.csv","Csv/UI/MakedSaveUI.csv","Csv/UI/TestSaveUI.csv" };

	//�w��t�H���_�̑��΃p�X(sln�t�@�C�����L��ꏊ����̃p�X)
	const std::string LOADFILEPASS = "graphics\\UI\\*.png";

	//****************---------------------------------------------------------------------------------------------------************//

	//���݂̃����[�h�p�X
	int nowReloadPass = static_cast<uint32_t>(UIFILE::DEFAULT);

	//�����[�h�p�X��ύX����֐�
	void ChangeReLoadPass();

	//���\�[�X�摜�̓ǂݍ���(�p�X�o�R �R�[�h�ł̎b��I�ȃf�o�b�O�Ɏg�p)
	void LoadResourceGraphic(std::string Pass, int Width, int Height);

	//debug�̂���public�Ɉړ�

	//���\�[�X�摜�̍ēǂݍ���(���s��ʒ��̃{�^���Ɏd���� ���i�͂�����Ń����[�h����)
	//�w�肵���t�H���_�̒��̑S�Ẳ摜��ǂݍ���
	void LoadFileResource();


	//Csv�����UI���[�h�֐�
	void LoadUI(std::string Pass);

	//���\�[�X�G���A�ɕ`�悷��摜�̐����T�C�Y
	const int DRAWSIZE = 100;

	//���\�[�X�G���A�̊���W(��ԏ�̉摜�̕`�撆�S���W)
	const tnl::Vector3 FIRSTRESOURCECENTERPOS = { 70, 70, 0 };

	//���񃊃\�[�X�摜�ǂݍ���(��{UI�̘g�̂ݕK���ǂݍ���)
	void LoadDefaultResource();

	//���\�[�X�摜�̕`��
	void DrawResource();

	//----------------------------------------------//

	//----------�V�[�N�G���X����---------------------//
	//�����V�[�N�G���X��ݒ�
	tnl::Sequence<UIEditor> mainSequence =
		tnl::Sequence<UIEditor>(this, &UIEditor::SeqSelect);

	//�e�V�[�N�G���X��Update�֐�
	bool SeqSelect(const float DeltaTime);
	bool SeqPlace(const float DeltaTime);
	bool SeqEdit(const float DeltaTime);

	//�V�[�N�G���X�ꗗ
	enum class SEQUENCE :uint32_t {
		SELECT,
		PLACE,
		EDIT,
		MAX
	};

	SEQUENCE nowSequence = SEQUENCE::SELECT;

	//�V�[�N�G���X�ύX�֐�
	bool ChangeSequence(SEQUENCE NextSeq);

	//�V�[�N�G���X���Ƃ̕`��֐�
	void DrawSelectSequence();
	void DrawPlaceSequence();
	void DrawEditSequence();

	//���݂̃V�[�N�G���X�̕`��֐�
	const std::function< void(UIEditor*) > DRAWSEQUENCE[3] = { &UIEditor::DrawSelectSequence,&UIEditor::DrawPlaceSequence,&UIEditor::DrawEditSequence };

	//-----------------------------------------------------------//
};

