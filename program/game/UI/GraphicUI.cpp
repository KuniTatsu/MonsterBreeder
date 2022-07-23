#include "GraphicUI.h"
#include"../Manager/GameManager.h"



//�g�̒��ɉ摜��`�悵�����ꍇ�͂������Ő�������
GraphicUI::GraphicUI(int FrameWidth, int FrameHeight, std::string UIGh, std::shared_ptr<UIData> FrameData, int Type)
{
	gManager = GameManager::Instance();

	uiType = Type;

	//�g��UI�f�[�^�̑��
	frameData = FrameData;

	//UI���摜�̉����擾
	width = FrameWidth;

	//UI���摜�̏c���擾
	height = FrameHeight;

	//3���������������擾
	splitLength = frameData->xSize;

	//UI�̍���̕`����W
	pos = frameData->leftTopPos;

	//���S���W���擾
	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);

	underBottomPosY = centerPos.y + (height >> 1) + 50;

	//�g�̉摜�̕������[�h
	//gManager->LoadDivGraphEx(FrameGh, 9, 3, 3, 16, 16, frameGh);
	LoadDivGraphEx(frameData->pass, frameData->allNum, frameData->widthNum, frameData->heightNum,
		frameData->xSize, frameData->ySize);

	drawGraphicPass = UIGh;
	//�g���ɕ`�悷��UI�摜�̃��[�h
	drawUIGh = gManager->LoadGraphEx(UIGh);
}

//�g�����~�����ꍇ�͂������Ő�������
GraphicUI::GraphicUI(int FrameWidth, int FrameHeight, std::shared_ptr<UIData> FrameData, int Type)
{
	gManager = GameManager::Instance();

	uiType = Type;

	//�g��UI�f�[�^�̑��
	frameData = FrameData;

	//UI���摜�̉����擾
	width = FrameWidth;

	//UI���摜�̏c���擾
	height = FrameHeight;

	//3���������������擾
	splitLength = frameData->xSize;

	//UI�̍���̕`����W
	pos = frameData->leftTopPos;

	//���S���W���擾
	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);

	underBottomPosY = centerPos.y + (height >> 1) + 50;

	//�����Ȃ��̏ꍇ�͂��̂܂܃��[�h����
	if (uiType == 1) {
		buttonGh = gManager->LoadGraphEx(frameData->pass);
		return;
	}

	//�g�̉摜�̕������[�h
	//gManager->LoadDivGraphEx(FrameGh, 9, 3, 3, 16, 16, frameGh);
	LoadDivGraphEx(frameData->pass, frameData->allNum, frameData->widthNum, frameData->heightNum,
		frameData->xSize, frameData->ySize);
}
/*
//�����L�΂��Ȃ��ꍇ�͂������Ő������� �����������̂Ŏg�p���Ȃ�
GraphicUI::GraphicUI(std::string Pass, int FrameWidth, int FrameHeight, std::shared_ptr<UIData> imageData, int Type)
{//�g��UI�f�[�^�̑��
	frameData = imageData;
	uiType = Type;

	gManager = GameManager::Instance();
	//buttonPass = frameData->pass;
	buttonGh = gManager->LoadGraphEx(frameData->pass);

	//UI���摜�̉����擾
	width = FrameWidth;

	//UI���摜�̏c���擾
	height = FrameHeight;

	//UI�̍���̕`����W
	pos = frameData->leftTopPos;
	//���S���W���擾
	centerPos = tnl::Vector3(pos.x + (width >> 1), pos.y + (height >> 1), 0);
}
*/

GraphicUI::~GraphicUI()
{
}

void GraphicUI::Draw()
{
	//�O�g�̕`��
	DrawFrame();
	//�摜���Ȃ���Ε`�悵�Ȃ�
	if (drawUIGh == -1)return;
	DrawRotaGraph(centerPos.x, centerPos.y, 0.98, 0, drawUIGh, true);
}
tnl::Vector3& GraphicUI::GetLeftTopPos()
{
	return frameData->leftTopPos;
}
//�J���}��؂�ɂ��ăf�[�^��Ԃ��֐�
std::string GraphicUI::GetCsvStringData(int Id)
{
	std::string data = std::to_string(Id) + "," + frameData->pass + "," + std::to_string(uiType) + "," + std::to_string(frameData->allNum) + "," + std::to_string(frameData->widthNum) + ","
		+ std::to_string(frameData->heightNum) + "," + std::to_string(frameData->xSize) + "," + std::to_string(frameData->ySize) + ","
		+ std::to_string(frameData->leftTopPos.x) + "," + std::to_string(frameData->leftTopPos.y) + "," + std::to_string(width) + ","
		+ std::to_string(height) + "," + drawGraphicPass;

	return data;
}
//�摜��Vector�ւ̕������[�h
void GraphicUI::LoadDivGraphEx(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize)
{
	//�ꎞ�ۊǗp�̔z��
	int* buf = new int[AllNum];
	//����
	LoadDivGraph(Pass.c_str(), AllNum, WidthNum, HeightNum, XSize, YSize, buf);

	//vector�Ɋi�[
	for (int i = 0; i < AllNum; ++i) {
		frameGh.emplace_back(buf[i]);
	}
	//�ꎞ�ۊǗp�z��̊J��
	delete[] buf;
}

void GraphicUI::ReLoadDivGraphic(std::string Pass, const int AllNum, const int WidthNum, const int HeightNum, int XSize, int YSize)
{
	//�摜�n���h���̏���
	frameGh.clear();
	//�摜�̕������[�h
	LoadDivGraphEx(Pass, AllNum, WidthNum, HeightNum, XSize, YSize);
}

void GraphicUI::ReLoadGraphic(std::string Pass)
{
	buttonGh = 0;
	buttonGh = gManager->LoadGraphEx(Pass);
}

void GraphicUI::DrawFrame()
{
	//�����摜�ł͂Ȃ��ꍇ�͂��̂܂ܕ`�悷��
	if (frameGh.empty()) {
		DrawRotaGraph(centerPos.x, centerPos.y, 1, 0, buttonGh, true);
		return;
	}
	//�g�̏�i�̕`��
	DrawGraph(pos.x, pos.y, frameGh[0], true);
	DrawExtendGraph(pos.x + splitLength, pos.y, pos.x + width - splitLength, pos.y + splitLength, frameGh[1], true);
	DrawGraph(pos.x + width - splitLength, pos.y, frameGh[2], true);

	//�g�̒��i�̕`��
	DrawExtendGraph(pos.x, pos.y + splitLength, pos.x + splitLength, pos.y + height - splitLength, frameGh[3], true);
	DrawExtendGraph(pos.x + splitLength, pos.y + splitLength, pos.x + width - splitLength, pos.y + height - splitLength, frameGh[4], true);
	DrawExtendGraph(pos.x + width - splitLength, pos.y + splitLength, pos.x + width, pos.y + height - splitLength, frameGh[5], true);

	//�g�̉��i�̕`��
	DrawGraph(pos.x, pos.y + height - splitLength, frameGh[6], true);
	DrawExtendGraph(pos.x + splitLength, pos.y + height - splitLength, pos.x + width - splitLength, pos.y + height, frameGh[7], true);
	DrawGraph(pos.x + width - splitLength, pos.y + height - splitLength, frameGh[8], true);
}

//------------GraphicUI�쐬�p�f�[�^�N���X----------------
UIData::UIData(std::string GraphicPass, int AllNum, int WidthNum, int HeightNum, int XSize, int YSize, float PosX, float PosY)
{
	pass = GraphicPass;
	allNum = AllNum;
	widthNum = WidthNum;
	heightNum = HeightNum;
	xSize = XSize;
	ySize = YSize;

	leftTopPos.x = PosX;
	leftTopPos.y = PosY;
}

UIData::~UIData()
{
}


