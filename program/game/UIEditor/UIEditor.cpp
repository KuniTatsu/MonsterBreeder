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
	//GameManager�C���X�^���X�擾
	gManager = GameManager::Instance();

	//���\�[�X�O���t�B�b�N���̔w�i����
	{
		auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 0.0f, 0.0f);
		resourcesFrame = std::make_shared<GraphicUI>(300, 768, data);
	}
	//�o�̓{�^���̐���
	{
		//auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 900.0f, 0.0f);
		saveButton = std::make_shared<GraphicUI>("graphics/UIEditor/SaveButton.png", 950.0f, 100.0f);
		SystemButtons.emplace_back(saveButton);
	}
	//���Z�b�g/�S�����{�^���̐���
	{
		//auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 900.0f, 110.0f);
		resetButton = std::make_shared<GraphicUI>("graphics/UIEditor/ResetButton.png", 950.0f, 210.0f);
		SystemButtons.emplace_back(resetButton);
	}
	//���[�h�{�^���̐���
	{
		//auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 900.0f, 220.0f);
		loadButton = std::make_shared<GraphicUI>("graphics/UIEditor/LoadButton.png", 950.0f, 320.0f);
		SystemButtons.emplace_back(loadButton);
	}
	//���[�h�ύX�{�^���̐���
	{
		//auto data = std::make_shared<UIData>("graphics/ModeNoEdit.png", 9, 3, 3, 16, 16, 900, 330);
		modeChangeButton = std::make_shared<GraphicUI>("graphics/UIEditor/ModeNoEdit.png", 950.0f, 430.0f);
		SystemButtons.emplace_back(modeChangeButton);
	}
}

void UIEditor::Update()
{
	//���݂̃V�[�N�G���X�̍X�V�֐��̎��s
	mainSequence.update(gManager->deltatime);
}

void UIEditor::Draw()
{
	//�ۑ����ꂽUI�̕`��
	for (auto ui : makedUI) {
		ui->Draw();
	}

	//���݂̃V�[�N�G���X�̊Ԃ̂ݕ`�悵�������e�̕`��
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);
}
void UIEditor::SaveUIButton()
{
}
void UIEditor::ResetUIButton()
{
}
void UIEditor::LoadUIButton()
{
}
void UIEditor::ModeChangeButton()
{
}
void UIEditor::UiToString()
{
}
void UIEditor::UiOutput()
{
}
//�摜�p�X����V�����摜���\�[�X�����[�h����
void UIEditor::LoadResourceGraphic(std::string Pass, int Width, int Height)
{

	auto pos = resources.back()->pos;
	pos.y += 100;

	//���\�[�X�𐶐�����
	auto resource = std::make_shared<Graphic>(tnl::Vector3(150, 100, 0), Pass, Width, Height);
	//�z��Ɋi�[
	resources.emplace_back(resource);

}
//����̃t�H���_�̒��ɂ������̊g���q�̉摜��ǂݍ���
void UIEditor::LoadFileResource()
{
	//���\�[�X�̔z�����ɂ���
	resources.clear();

	//�\���� info.Name�Ńt�@�C�������擾�ł���
	FILEINFO info;

	//�t�@�C�������邩�ǂ����̃t���O
	DWORD_PTR FindHandle;

	//�����J�n�@�t�H���_���̍ŏ��̃t�@�C���̏����擾
	//�t�H���_����.png�`���̉摜�݂̂���������
	//�������Ƀt�H���_�̎��s�t�@�C������̑��΃p�X������
	FindHandle = FileRead_findFirst(LOADFILEPASS.c_str(), &info);

	//�����ŏ��̃t�@�C�������������瑖�鏈��
	if (FindHandle != (DWORD_PTR)-1)
	{
		//�������[�v����
		while (1) {
			////���̃t�@�C���������B���������烋�[�v�𔲂��ďI��
			//if (FileRead_findNext(FindHandle, &info) < 0)break;

			//�t�@�C�������擾
			std::string name = info.Name;

			//�摜�����[�h
			int gh = gManager->LoadGraphEx("graphics/UI/" + name);

			//�������\�[�X�̔z�񂪋󂾂����珉���|�W�V�����Ő�������
			if (resources.empty()) {
				//���\�[�X�𐶐�����
				auto resource = std::make_shared<Graphic>(tnl::Vector3(70, 70, 0), gh);
				//�z��Ɋi�[
				resources.emplace_back(resource);

				//���̃t�@�C���������B���������烋�[�v�𔲂��ďI��
				if (FileRead_findNext(FindHandle, &info) < 0)break;
				continue;
			}
			else {
				//��O�̃��\�[�X�̕`����W���擾����
				auto pos = resources.back()->pos;
				//�摜���m�̊Ԋu
				pos.y += 110;

				//���\�[�X�𐶐�����
				auto resource = std::make_shared<Graphic>(pos, gh);
				//�z��Ɋi�[
				resources.emplace_back(resource);
			}
			//���̃t�@�C���������B���������烋�[�v�𔲂��ďI��
			if (FileRead_findNext(FindHandle, &info) < 0)break;
		}
		//�����n���h���̏���
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
		//�ǂ�ȑf�މ摜��100x100�ɏk�����ĕ`�悷��
		DrawExtendGraph(resource->pos.x - 50, resource->pos.y - 50, resource->pos.x + 50, resource->pos.y + 50, resource->gh, true);
	}
}

//��ʂɐݒu����UI�摜�����[�̉摜���X�g����I�ԃV�[�N�G���X �f�t�H���g���
bool UIEditor::SeqSelect(const float DeltaTime)
{
	//���[�h�{�^�����������Ƃ��̏���


	return true;
}
//Select�V�[�N�G���X�őI��UI�摜��u���ꏊ�����߂�V�[�N�G���X �傫���ύX���s��Ȃ��ꍇ��Select�ɖ߂�
bool UIEditor::SeqPlace(const float DeltaTime)
{
	return true;
}
//Place�V�[�N�G���X�Œu����UI�̉E���������L�΂��A�傫���ύX���s���V�[�N�G���X
bool UIEditor::SeqEdit(const float DeltaTime)
{
	return true;
}

void UIEditor::DrawSelectSequence()
{
	//���\�[�X�̕\��
	//�w�i
	resourcesFrame->Draw();
	DrawResource();

	//�Z�[�u�A���Z�b�g�A���[�h�A���[�h�ύX�{�^���̕\��
	for (auto &button : SystemButtons) {
		button->Draw();
	}
}

void UIEditor::DrawPlaceSequence()
{
}

void UIEditor::DrawEditSequence()
{
}
//Csv�f�[�^����UI�����[�h����֐� �f�[�^�̕��я������킹�邱��
void UIEditor::LoadUI(std::string Pass)
{
	//��ʓ��̑S�Ă�UI����������
	makedUI.clear();

	//CSV�ǂݍ���
	auto loadUICsv = tnl::LoadCsv(Pass);

	//1�s�ڂ���X�^�[�g(0�s�ڂ͍��ږ�)
	for (int i = 1; i < loadUICsv.size(); ++i) {

		//------string�^�̃f�[�^��int�^��float�^�ɕϊ����A���[�J���ϐ��ɕۊǂ��鏈��----//
		//type 0:�������[�h,1:���̂܂܃��[�h
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

		//�摜�������L�΂����Ɏg��UI�̏ꍇ
		if (type == static_cast<uint32_t>(LOADMODE::NORMAL)) {

			float centerX = posX + (widthSize / 2);
			float centerY = posY + (heightSize / 2);

			//GraphicUI�N���X�𐶐�(�摜���g�傹���Ɏg���ꍇ)
			auto newUI = std::make_shared<GraphicUI>(loadUICsv[i][1], centerX, centerY);
			//vector�ɓo�^
			makedUI.emplace_back(newUI);
			//���̃��[�v��
			continue;
		}


		//UIData�N���X�𐶐�
		auto data = std::make_shared<UIData>(loadUICsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, posX, posY);

		if (loadUICsv[i][11] == "") {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜���Ȃ��ꍇ)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data);

			//vector�ɓo�^
			makedUI.emplace_back(newUI);
		}
		else {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜������ꍇ
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][11], data);

			//vector�ɓo�^
			makedUI.emplace_back(newUI);
		}
	}
}
