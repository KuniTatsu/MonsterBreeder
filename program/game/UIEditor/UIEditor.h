#pragma once
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

�g�̂݁A�g�Ɖ摜�A�摜�݂̂��I�ׂ邱��

���R�g�傩�A���䗦�g�傩�A���{��I�ׂ邱��

�����̐F���ύX�ł��邱��
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

	//Csv�����UI���[�h�֐�
	void LoadUI(std::string Pass);

	//���\�[�X�摜�̍ēǂݍ���(���s��ʒ��̃{�^���Ɏd���� ���i�͂�����Ń����[�h����)
		//�w�肵���t�H���_�̒��̑S�Ẳ摜��ǂݍ���
	void LoadFileResource();

private:
	//gamemanager
	GameManager* gManager = nullptr;

	int mouseX = 0;
	int mouseY = 0;

	//�쐬�A�ǂݍ���UI�̔z��
	std::vector<std::shared_ptr<GraphicUI>> makedUI;

	//���\�[�X�摜�̔z��
	std::vector<std::shared_ptr<Graphic>>resources;

	//select�V�[�N�G���X�őI�������摜���\�[�X�|�C���^
	std::shared_ptr<Graphic>nowSelectGraphic = nullptr;

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

	//mode���Ƃ̎g�p�摜�z��
	const std::string MODEGRAPHICPASS[static_cast<uint32_t>(EDITMODE::MAX)] = { "graphics/UIEditor/ModeNoEdit.png","graphics/UIEditor/ModeSameRatio.png","graphics/UIEditor/ModeFreeRatio.png" };

	//���݂̃��[�h�@�t�H���g�͊g��Ȃ�
	int nowMode = static_cast<uint32_t>(EDITMODE::NOEDIT);

	//�g�僂�[�h��ύX����֐�
	inline void ChangeEditMode() {
		//�N���b�N���邲�Ƃ�0->1->2->0->...�̏��ŏz����@
		nowMode = (nowMode + 1) % static_cast<uint32_t>(EDITMODE::MAX);
	}
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

	//�g�僂�[�h�̕ύX�{�^��
	std::shared_ptr<GraphicUI> modeChangeButton = nullptr;

	//�V�X�e��UI�̃{�^���z��
	std::vector<std::shared_ptr<GraphicUI>>SystemButtons;
	//�V�X�e��UI
	enum class SYSTEMUI :uint32_t {
		SAVE,
		RESET,
		LOAD,
		CHANGE,
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
	//change�{�^��
	void ModeChangeButton();

	//�{�^�����������Ƃ��̏��������Ă����֐��̔z��
	const std::function< void(UIEditor*) > BUTTONPROCESS[4] = { &UIEditor::SaveUIButton,&UIEditor::ResetUIButton,
																&UIEditor::LoadUIButton,&UIEditor::ModeChangeButton };

	//---------�A�E�g�v�b�g�p-------------//
	//�o�͗p���`�ςݕ�����z��
	std::vector<std::string> UIText;

	//�o�͗p�̕�����^�Ƀf�[�^�𐮌`����֐�
	void UiToString();
	//�o�͊֐� �J���}��؂�̃f�[�^�ŏo��
	void UiOutput();
	//--------------------------------------//


	//----------UIEditor�̃��\�[�X�֌W�̊֐�----------//

	//���\�[�X�摜�̓ǂݍ���(�p�X�o�R �R�[�h�ł̎b��I�ȃf�o�b�O�Ɏg�p)
	void LoadResourceGraphic(std::string Pass, int Width, int Height);

	//debug�̂���public�Ɉړ�
	/*
	//���\�[�X�摜�̍ēǂݍ���(���s��ʒ��̃{�^���Ɏd���� ���i�͂�����Ń����[�h����)
	//�w�肵���t�H���_�̒��̑S�Ẳ摜��ǂݍ���
	void LoadFileResource();
	*/

	//�����[�h�Ώ�
	enum class UIFILE :uint32_t {
		DEFAULT,
		SAVED,
		DEBUG,
		MAX
	};
	//UI���[�h�Ώۂ̃p�X
	const std::string RELOADPASS[static_cast<uint32_t>(UIFILE::MAX)] = { "Csv/UI/SaveUI.csv","Csv/UI/TestSaveUI.csv","Csv/UI/TestSaveUI.csv" };

	//�w��t�H���_�̑��΃p�X(sln�t�@�C�����L��ꏊ����̃p�X)
	const std::string LOADFILEPASS = "graphics\\UI\\*.png";

	//���\�[�X�G���A�ɕ`�悷��摜�̐����T�C�Y
	const int DRAWSIZE = 100;

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


};

