#pragma once
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

//------------�T�v----------------//
//UIEditor�Ŏg��UI�摜�����[�ɕ��ׂ邽�߂̃N���X
//�ʒu���ƃn���h���A�傫���Ȃǂ�ێ�����

class GameManager;

class Graphic {

public:
	//gh���g�p�������� ���ƍ����̓f�t�H���g������100�Ɏw��(extendGraph���g������)
	Graphic(tnl::Vector3 Pos, int Gh, int Width = 100, int Height = 100);
	//�t�@�C���p�X���g�p��������
	Graphic(tnl::Vector3 Pos, std::string Pass, int Width, int Height);

	//�`�撆�S���W
	tnl::Vector3 pos = {};
	//�O���t�B�b�N�n���h��
	int gh = 0;
	//����
	int width = 0;
	//�c��
	int height = 0;

	GameManager* gManager = nullptr;


};