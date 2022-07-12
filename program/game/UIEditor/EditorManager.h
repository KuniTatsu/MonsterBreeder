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

	//main�V�[�N�G���X�őI�񂾃O���t�B�b�N �ʒu�Ƒ傫�������߂邽�߂Ɏg��
	Graphic* nowSelectGraphic = nullptr;
	//�傫���ύX���̃O���t�B�b�N
	//std::vector<Graphic*>editGraphic;

	//std::vector<GraphicUI*>editMenu;

	//�ŏI����ʒu�̃O���t�B�b�N
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

	//�����V�[�N�G���X��ݒ�
	tnl::Sequence<EditorManager> main_sequence_ =
		tnl::Sequence<EditorManager>(this, &EditorManager::Seq_main);

	//UI�摜��I�ԃV�[�N�G���X
	bool Seq_main(const float deltatime);
	//UI�摜��u���܂ł̃V�[�N�G���X
	bool Seq_Place(const float deltatime);
	//UI�摜�������L�΂��V�[�N�G���X
	bool Seq_Edit(const float deltatime);


	//�V�[�N�G���X�̗񋓑�
	enum class SEQUENCE {
		main,
		place,
		edit,
		MAX
	};
	//���̃V�[�N�G���X
	SEQUENCE nowSeq = SEQUENCE::main;


	std::vector<std::string> UIText;
	//�V�[�N�G���X��ύX����֐�
	void ChangeSequence(SEQUENCE seq);
	//���݂̃V�[�N�G���X����`�悷��֐�
	void DrawNowSeqName(SEQUENCE seq);

	//��ʓ���UI�����Z�b�g�A�S��������֐�
	void Reset();

	//---------�A�E�g�v�b�g�p-------------//
	//�o�͗p�̕�����^�Ƀf�[�^�𐮌`����֐�
	void UiToString();
	//�o�͊֐� �J���}��؂�̃f�[�^�ŏo��
	void UiOutput();


};