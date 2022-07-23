#include "UIEditor.h"
#include<fstream>
#include"../UI/GraphicUI.h"
#include"../UIEditor/Graphic.h"
#include"../Manager/GameManager.h"

using namespace std;

UIEditor::UIEditor()
{
}
//�f�X�g���N�^�ł͊e���X�g�Avector�̒��g���������A���������J��������
UIEditor::~UIEditor()
{
	SystemButtons.clear();
	makedUI.clear();
	resources.clear();
	UIText.clear();
}
//�G�f�B�^�[�̏������֐�
void UIEditor::Init()
{
	//GameManager�C���X�^���X�擾
	gManager = GameManager::Instance();
	//�������\�[�X�摜�̃��[�h ���Ɣ���UI�w�i
	LoadDefaultResource();

	//���\�[�X�O���t�B�b�N���̔w�i����
	{
		auto data = std::make_shared<UIData>("graphics/FrameBlack.png", 9, 3, 3, 16, 16, 0.0f, 0.0f);
		resourcesFrame = std::make_shared<GraphicUI>(300, 768, data, static_cast<uint32_t>(LOADMODE::SPLIT));
	}
	//�o�̓{�^���̐���
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/SaveButton.png", 1, 1, 1, 100, 100, 900.0f, 0.0f);
		saveButton = std::make_shared<GraphicUI>(100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(saveButton);
	}
	//���Z�b�g/�S�����{�^���̐���
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/ResetButton.png", 1, 1, 1, 100, 100, 900.0f, 110.0f);
		resetButton = std::make_shared<GraphicUI>(100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(resetButton);
	}
	//���[�h�{�^���̐���
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/LoadButton.png", 1, 1, 1, 100, 100, 900.0f, 220.0f);
		loadButton = std::make_shared<GraphicUI>(100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(loadButton);
	}
	//���[�h��ύX�{�^���̐���
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/ReloadDefault.png", 1, 1, 1, 100, 100, 900.0f, 330.0f);
		reloadChangeButton = std::make_shared<GraphicUI>(100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(reloadChangeButton);
	}

	//���[�h�ύX�{�^���̐���
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/ModeNoEdit.png", 1, 1, 1, 100, 100, 900.0f, 440.0f);
		modeChangeButton = std::make_shared<GraphicUI>(100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(modeChangeButton);
	}
	//���\�[�X���[�h�{�^���̐���
	{
		auto data = std::make_shared<UIData>("graphics/UIEditor/ResourceLoadButton.png", 1, 1, 1, 100, 100, 900.0f, 550.0f);
		resourceButton = std::make_shared<GraphicUI>(100, 100, data, static_cast<uint32_t>(LOADMODE::NORMAL));
		SystemButtons.emplace_back(resourceButton);
	}

}
//------------------------���t���[���O������Ăяo���֐��Q---------------------------------------//
void UIEditor::Update()
{
	//�N�����Ă��Ȃ���Έ�؂̏��������Ȃ�
	if (!isEnable)return;

	//�}�E�X�|�W�V�����擾
	GetMousePoint(&mouseX, &mouseY);
	//���݂̃V�[�N�G���X�̍X�V�֐��̎��s
	mainSequence.update(gManager->deltatime);
}

void UIEditor::Draw()
{
	//�N�����Ă��Ȃ���Έ�؂̏��������Ȃ�
	if (!isEnable)return;
	//�ۑ����ꂽUI�̕`��
	for (auto ui : makedUI) {
		ui->Draw();
	}

	//���݂̃V�[�N�G���X�̊Ԃ̂ݕ`�悵�������e�̕`��
	DRAWSEQUENCE[static_cast<uint32_t>(nowSequence)](this);
}

//-----------------------------------------------------------------------------------------------//

//���R�g��֐�
void UIEditor::EditFreeScale()
{
	//�}�E�X�ɒǏ]���ĕ��ƍ��������R�ɓ���
	edit->SetUIWidth(static_cast<int>(mouseX - leftTop.x));
	edit->SetUIHeight(static_cast<int>(mouseY - leftTop.y));
}
//���䗦�g��֐�
void UIEditor::EditSameScale()
{
	//�}�E�X���W�̐�Βl�̑傫�������擾����
	int maxMouse = 0;
	//mouse��X���W�܂ł̕��ō������ړ�������
	if (mouseX >= mouseY) {
		maxMouse = mouseX;

		//����̍��W����傫�����܂ł̋�����X��Y�𓮂���
		edit->SetUIWidth(static_cast<int>(maxMouse - leftTop.x));
		edit->SetUIHeight(static_cast<int>(maxMouse - leftTop.x));
	}
	//mouse��Y���W�܂ł̍����ŕ����ړ�������
	else {
		maxMouse = mouseY;

		//����̍��W����傫�����܂ł̋�����X��Y�𓮂���
		edit->SetUIWidth(static_cast<int>(maxMouse - leftTop.y));
		edit->SetUIHeight(static_cast<int>(maxMouse - leftTop.y));
	}
}
//�e�{�^���̊��m�֐�
void UIEditor::CheckButtonClick()
{
	//�}�E�X���E���̃G���A�ɂȂ������炻���������肵�Ȃ�
	if (mouseX < 700)return;

	//�S�Ẵ{�^����Ώۂ�for���Ŋm�F����
	for (int i = 0; i < SystemButtons.size(); ++i) {

		//�{�^���̍���̍��W���擾
		tnl::Vector3 leftTopPos = SystemButtons[i]->GetLeftTopPos();
		//�����{�^�����N���b�N����Ă�����
		if (gManager->isClickedRect(mouseX, mouseY, leftTopPos.x, leftTopPos.y,
			leftTopPos.x + SystemButtons[i]->GetUIWidth(), leftTopPos.y + SystemButtons[i]->GetUIHeight()))
		{
			//i�Ԃ̊֐������s ������this�|�C���^ �V���݂����Ȃ���
			BUTTONPROCESS[i](this);
			break;
		}
	}
}
//�Z�[�u�{�^�����������Ƃ��̏���
void UIEditor::SaveUIButton()
{
	tnl::DebugTrace("\n�Z�[�u�{�^���������ꂽ��\n");
	//�J���}��؂�̃e�L�X�g�f�[�^�ɕϊ�
	UiToString();
	//�w�肵���p�X��Csv�t�@�C���𐶐�or�㏑��
	UiOutput();
}
//���Z�b�g�{�^���̏���
void UIEditor::ResetUIButton()
{
	tnl::DebugTrace("\nReset�{�^���������ꂽ��\n");
	//��ʂ̒��ɂ���UI��S�ď�������
	makedUI.clear();
}
//���[�h�{�^���̏���
void UIEditor::LoadUIButton()
{
	tnl::DebugTrace("\nLoad�{�^���������ꂽ��\n");
	//�W���̓ǂݍ��݃p�X��UI�����[�h����
	LoadUI(RELOADPASS[nowReloadPass]);
}
//�`�F���W�{�^���̏���
void UIEditor::ModeChangeButton()
{
	tnl::DebugTrace("\nChange�{�^���������ꂽ��\n");
	//�g�僂�[�h����i�߂�
	ChangeEditMode();
	//�摜��ύX
	modeChangeButton->ReLoadGraphic(MODEGRAPHICPASS[nowMode]);

	tnl::DebugTrace("\nMODE:");
	tnl::DebugTrace(MODESTRING[nowMode].c_str());
	tnl::DebugTrace("\n");

}
//UI��CSV�o�͂���ۂ̃J���}��؂�f�[�^�̕�����ɕϊ�����֐�
void UIEditor::UiToString()
{
	int idCount = 0;
	for (auto ui : makedUI) {

		std::string data = ui->GetCsvStringData(idCount);

		UIText.emplace_back(data);
		idCount++;
	}
}
//Csv�f�[�^�̏o�͊֐�
void UIEditor::UiOutput()
{
	//ofstream�^�̕ϐ� �J�����t�@�C�����W�J�����
	std::ofstream writingfile;
	//���΃p�X
	//std::string filename = "Csv/UI/MakedSaveUI.csv";
	std::string filename = RELOADPASS[static_cast<uint32_t>(UIFILE::SAVED)];

	//�p�X����o�͐ݒ�Ńt�@�C�����J��
	writingfile.open(filename, std::ios::out);

	//0�s�ڂ����͐�ɏ�������
	writingfile << "id, frameGhPass, type 0:split, 1 : normal, allNum, widthNum, heightNum, widthSize, heightSize, leftTopPos.x, leftTopPos.y, FrameWidth, FrameHeight, ingraphicsPass" << std::endl;

	//UIText�ɂ�����e��S��csv�t�@�C���ɏ�������
	for (auto outText : UIText) {
		writingfile << outText << std::endl;
	}
	//�J�����t�@�C���̊J��
	writingfile.close();
}
//���[�h����UI��CSV�t�@�C���p�X��ύX����֐�
void UIEditor::ChangeReLoadPass() {
	nowReloadPass = (nowReloadPass + 1) % static_cast<uint32_t>(UIFILE::MAX);
	reloadChangeButton->ReLoadGraphic(LOADGRAPHICPASS[nowReloadPass]);
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
//�摜���\�[�X���t�H���_����ǂݍ���
void UIEditor::ResourceButton()
{
	//���\�[�X�̔z�����ɂ���
	resources.clear();
	LoadDefaultResource();
	LoadFileResource();
}
//���[�h����CSV��ύX����
void UIEditor::ChangeLoadCSV()
{
	ChangeReLoadPass();
}
//����̃t�H���_�̒��ɂ������̊g���q�̉摜��ǂݍ���
void UIEditor::LoadFileResource()
{
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

			//filePass
			std::string filePass = "graphics/UI/" + name;

			//�摜�����[�h
			//int gh = gManager->LoadGraphEx(filePass);

			//�������\�[�X�̔z�񂪋󂾂����珉���|�W�V�����Ő�������
			if (resources.empty()) {
				//���\�[�X�𐶐�����
				auto resource = std::make_shared<Graphic>(FIRSTRESOURCECENTERPOS, filePass);
				//�z��Ɋi�[
				resources.emplace_back(resource);

				//���̃t�@�C���������B���������烋�[�v�𔲂��ďI��
				if (FileRead_findNext(FindHandle, &info) < 0)break;
				continue;
			}
			//���\�[�X�����łɈ�ȏ㑶�݂�����
			else {
				//��O�̃��\�[�X�̕`�撆�S���W���擾����
				auto pos = resources.back()->pos;
				//�摜�̑傫���Ɖ摜���m�̊Ԋu�ŋ������J����
				pos.y += DRAWSIZE + 20;

				//���\�[�X�𐶐�����
				auto resource = std::make_shared<Graphic>(pos, filePass);
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
//UIEditor�̗L����Ԃ�؂�ւ���֐� �O������Ă�
void UIEditor::ChangeEnable()
{
	//�L����ԂŌĂ΂ꂽ�疳���ɂ���
	if (isEnable) {
		isEnable = false;
		makedUI.clear();
		UIText.clear();
		return;
	}
	isEnable = true;
}
//���\�[�X�摜�I�����m�֐�
bool UIEditor::CheckSelectResource()
{
	//�}�E�X�������ɂ��Ȃ���΂����������肵�Ȃ�
	if (mouseX > 300)return false;

	for (auto graphic : resources) {
		//���N���b�N���m
		if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
			//������W
			int topLeftX = graphic->pos.x - DRAWSIZE / 2;
			int topLeftY = graphic->pos.y - DRAWSIZE / 2;

			//�E�����W
			int bottomRightX = graphic->pos.x + DRAWSIZE / 2;
			int bottomRightY = graphic->pos.y + DRAWSIZE / 2;

			//���\�[�X�摜���N���b�N���Ă�����
			//if (gManager->isClickedRect(mouseX, mouseY, topLeftX, topLeftY, bottomRightX, bottomRightY)) {
			if (gManager->isClickedRect(mouseX, mouseY, topLeftX, topLeftY, bottomRightX, bottomRightY)) {
				//�I�𒆂̉摜�Ƀ|�C���^�������
				nowSelectGraphic = graphic;
				//�ݒu�V�[�N�G���X�Ɉړ�����
				//ChangeSequence(SEQUENCE::PLACE);

				//true���A��ΐݒu�V�[�N�G���X�Ɉړ�������
				return true;
			}
		}
	}
	//false���A��ƃV�[�N�G���X���ړ����Ȃ�
	return false;
}
//����Ƀ��[�h���镪�������L�΂��̃f�t�H���gUI
void UIEditor::LoadDefaultResource()
{
	auto black = std::make_shared<Graphic>(tnl::Vector3(70, 70, 0), "graphics/FrameBlack.png", 48, 48);
	auto white = std::make_shared<Graphic>(tnl::Vector3(70, 180, 0), "graphics/FrameWhite.png", 48, 48);

	resources.emplace_back(black);
	resources.emplace_back(white);
}
//��ʍ��[�ɕ`�悷��f�މ摜
void UIEditor::DrawResource()
{
	for (auto resource : resources) {
		//�ǂ�ȑf�މ摜��100x100�ɏk�����ĕ`�悷��
		DrawExtendGraph(resource->pos.x - DRAWSIZE / 2, resource->pos.y - DRAWSIZE / 2,
			resource->pos.x + DRAWSIZE / 2, resource->pos.y + DRAWSIZE / 2, resource->gh, true);
	}
}

//��ʂɐݒu����UI�摜�����[�̉摜���X�g����I�ԃV�[�N�G���X �f�t�H���g���
bool UIEditor::SeqSelect(const float DeltaTime)
{
	//�Z�[�u�Ȃǂ̃{�^���N���b�N���m
	CheckButtonClick();

	//���\�[�X�G���A����摜��I�� 
	//true���A���Ă���Ή摜��I��ł���̂ŁA�ݒu�V�[�N�G���X�Ɉړ�����
	if (CheckSelectResource())ChangeSequence(SEQUENCE::PLACE);


	return true;
}
//Select�V�[�N�G���X�őI��UI�摜��u���ꏊ�����߂�V�[�N�G���X �傫���ύX���s��Ȃ��ꍇ��Select�ɖ߂�
bool UIEditor::SeqPlace(const float DeltaTime)
{
	//�N���b�N�����炻�̈ʒu�ŐV����GraphicUI�𐶐����AmakedUI�ɓo�^����
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {

		//�g�債�Ȃ��ꍇ
		if (nowMode == static_cast<uint32_t>(EDITMODE::NOEDIT)) {

			//UI�̃f�[�^�N���X���쐬
			auto data = std::make_shared<UIData>(nowSelectGraphic->filePass, 1, 1, 1, nowSelectGraphic->width, nowSelectGraphic->height,
				static_cast<float>(mouseX - nowSelectGraphic->width / 2), static_cast<float>(mouseY - nowSelectGraphic->height / 2));
			//UI���쐬
			auto newGraphicUI = std::make_shared<GraphicUI>(nowSelectGraphic->width, nowSelectGraphic->height, data, static_cast<uint32_t>(LOADMODE::NORMAL));

			//�쐬�ς�vector�ɓo�^
			makedUI.emplace_back(newGraphicUI);

			//�ꎞ�f�[�^�̏���
			nowSelectGraphic = nullptr;
			tnl::DebugTrace("\nnowSelectGraphic�����������܂���\n");

			//�V�[�N�G���X��߂�
			ChangeSequence(SEQUENCE::SELECT);
			return true;
		}
		//�g�傷��ꍇ
		else {
			//UI�̃f�[�^�N���X���쐬
			auto data = std::make_shared<UIData>(nowSelectGraphic->filePass, 9, 3, 3, static_cast<int>(nowSelectGraphic->width / 3), static_cast<int>(nowSelectGraphic->height / 3),
				static_cast<float>(mouseX - nowSelectGraphic->width / 2), static_cast<float>(mouseY - nowSelectGraphic->height / 2));

			//UI���쐬
			auto newGraphicUI = std::make_shared<GraphicUI>(nowSelectGraphic->width, nowSelectGraphic->height, data, static_cast<uint32_t>(LOADMODE::SPLIT));
			edit = newGraphicUI;

			//�V�[�N�G���X��Edit�Ɉړ�����
			ChangeSequence(SEQUENCE::EDIT);
			return true;
		}
	}
	return true;
}
//Place�V�[�N�G���X�Œu����UI�̉E���������L�΂��A�傫���ύX���s���V�[�N�G���X
bool UIEditor::SeqEdit(const float DeltaTime)
{
	//���̃V�[�N�G���X�ɓ�������t���[���ڂ����Ă�
	if (mainSequence.isStart()) {
		//����̍��W�̎擾->��_ ����͓������Ȃ�
		leftTop = edit->GetLeftTopPos();
	}

	//mode��Free�Ȃ玩�R�g��֐�->���ƍ��������R�Ɍ��߂�
	if (nowMode == static_cast<uint32_t>(EDITMODE::FREERATIO)) {
		EditFreeScale();
	}
	//mode��same�Ȃ瓖�䗦�g��֐�->���ƍ�������Ɍ��摜�̔䗦�Ɠ���
	else if (nowMode == static_cast<uint32_t>(EDITMODE::SAMERATIO)) {
		EditSameScale();
	}

	//���N���b�N��������傫��������AmakedUI�ɓo�^���Ă����܂ł̈ꎞ�f�[�^����������
	if (tnl::Input::IsMouseTrigger(tnl::Input::eMouseTrigger::IN_LEFT)) {
		//�o�^
		makedUI.emplace_back(edit);

		//�ꎞ�f�[�^�̏���
		nowSelectGraphic = nullptr;
		tnl::DebugTrace("\nnowSelectGraphic�����������܂���\n");
		edit = nullptr;
		tnl::DebugTrace("\nedit�����������܂���\n");

		ChangeSequence(SEQUENCE::SELECT);
		return true;
	}

	return true;
}

//�V�[�N�G���X�ύX�֐�
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
//Select�V�[�N�G���X�ł̕`��
void UIEditor::DrawSelectSequence()
{
	//���\�[�X�̕\��
	//�w�i
	resourcesFrame->Draw();
	DrawResource();

	//�Z�[�u�A���Z�b�g�A���[�h�A���[�h�ύX�{�^���̕\��
	for (auto& button : SystemButtons) {
		button->Draw();
	}
}
//Place�V�[�N�G���X�ł̕`��
void UIEditor::DrawPlaceSequence()
{
	//�}�E�X�ɑI�𒆂̉摜��Ǐ]������
	DrawRotaGraph(mouseX, mouseY, 1, 0, nowSelectGraphic->gh, true);
}
//Edit�V�[�N�G���X�ł̕`��
void UIEditor::DrawEditSequence()
{
	//�傫���ύX���̕����摜��`��
	edit->Draw();
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

		//UIData�N���X�𐶐�
		auto data = std::make_shared<UIData>(loadUICsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, posX, posY);

		//�摜�������L�΂����Ɏg��UI�̏ꍇ ->�g���R���X�g���N�^�𓝈ꂵ��
		if (type == static_cast<uint32_t>(LOADMODE::NORMAL)) {

			//GraphicUI�N���X�𐶐�(�摜���g�傹���Ɏg���ꍇ)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);
			//vector�ɓo�^
			makedUI.emplace_back(newUI);
			//���̃��[�v��
			continue;
		}
		if (loadUICsv[i][12] == "none") {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜���Ȃ��ꍇ)
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, data, type);

			//vector�ɓo�^
			makedUI.emplace_back(newUI);
		}
		else {
			//GraphicUI�N���X�𐶐�(�g�̒��ɉ摜������ꍇ
			auto newUI = std::make_shared<GraphicUI>(frameWidth, frameHeight, loadUICsv[i][12], data, type);

			//vector�ɓo�^
			makedUI.emplace_back(newUI);
		}
	}
}
