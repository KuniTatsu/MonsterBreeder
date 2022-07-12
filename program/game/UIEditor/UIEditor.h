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
	void ReLoadResource();


private:
	//gamemanager
	GameManager* gManager = nullptr;

	int mouseX = 0;
	int mouseY = 0;

	//�쐬�A�ǂݍ���UI�̔z��
	std::vector<std::shared_ptr<GraphicUI>> makedUI;

	//���\�[�X�摜�̔z��
	std::vector<std::shared_ptr<Graphic>>resources;

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
	GraphicUI* resourcesFrame = nullptr;
	//���݂�UI��csv�Ƃ��ďo�͂���{�^��
	GraphicUI* saveButton = nullptr;
	//���݂̉�ʂ�UI��S�ă��Z�b�g����{�^��
	GraphicUI* resetButton = nullptr;
	//����̖��O��csv����UI�����[�h���\������{�^��
	GraphicUI* loadButton = nullptr;

	//�g�僂�[�h�̕ύX�{�^��
	GraphicUI* modeChangeButton = nullptr;

	//���\�[�X�摜�̓ǂݍ���(�p�X�o�R �R�[�h�ł̎b��I�ȃf�o�b�O�Ɏg�p)
	void LoadResourceGraphic(std::string Pass,int Width,int Height);

	////���\�[�X�摜�̍ēǂݍ���(���s��ʒ��̃{�^���Ɏd���� ���i�͂�����Ń����[�h����)
	////�w�肵���t�H���_�̒��̑S�Ẳ摜��ǂݍ���
	//void ReLoadResource();

	//���񃊃\�[�X�摜�ǂݍ���(��{UI�̘g�̂ݕK���ǂݍ���)
	void LoadDefaultResource();

	//���\�[�X�摜�̕`��
	void DrawResource();

	//----------------------------------------------//

	//�V�[�N�G���X����
	//�����V�[�N�G���X��ݒ�
	tnl::Sequence<UIEditor> mainSequence =
		tnl::Sequence<UIEditor>(this, &UIEditor::SeqSelect);

	bool SeqSelect(const float DeltaTime);
	bool SeqPlace(const float DeltaTime);
	bool SeqEdit(const float DeltaTime);

	enum class SEQUENCE :uint32_t {
		SELECT,
		PLACE,
		EDIT,
		MAX
	};

	SEQUENCE nowSequence = SEQUENCE::SELECT;

	//�V�[�N�G���X���Ƃ̕`��֐�
	void DrawSelectSequence();
	void DrawPlaceSequence();
	void DrawEditSequence();

	//���݂̃V�[�N�G���X�̕`��֐�
	const std::function< void(UIEditor*) > DRAWSEQUENCE[3] = { &UIEditor::DrawSelectSequence,&UIEditor::DrawPlaceSequence,&UIEditor::DrawEditSequence };


};

