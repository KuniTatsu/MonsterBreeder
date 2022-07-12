#pragma once
#include<functional>
#include"Object.h"

class Player :public Object
{
public:
	//���[�J�����W������
	Player(int StartX, int StartY);
	~Player();

	//���t���[�����s�̍X�V�֐�
	void Update();
	//���t���[�����s�̕`��֐�
	void Draw();

	//�����m�F�֐�
	void CheckIsLive();

private:
	//�������֐�
	void Init();

	//�ړ��֐� �㉺���E

	void MoveUp();

	void MoveRight();

	void MoveDown();

	void MoveLeft();

	void MoveDummy() {};


	const std::function< void(Player*) > MOVEFUNC[4] = { &Player::MoveUp,&Player::MoveRight,&Player::MoveDown,&Player::MoveLeft };


};

