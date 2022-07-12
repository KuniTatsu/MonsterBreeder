#include "Player.h"
#include"../Manager/GameManager.h"


Player::Player(int StartX, int StartY)
{
	localPos.x = StartX;
	localPos.y = StartY;

	drawPos = { (localPos.x + 1) * 32 / 2,(localPos.y + 1) * 32 / 2,0 };

	gManager = GameManager::Instance();

	gh = gManager->LoadGraphEx("graphics/testPlayer.png");
}

Player::~Player()
{
}

void Player::Update()
{
	//�ړ����m����
	for (int i = 0; i < static_cast<uint32_t>(GameManager::KEYDIR::MAX); ++i) {
		if (tnl::Input::IsKeyDownTrigger(gManager->nowDirKeys[i])) {
			//�ړ��֐��̔z�񂩂�Y����������̕����Ă�
			MOVEFUNC[i](this);

			//�`����W�̍X�V
			SetPos(gManager->LocalToWorld(localPos));
		}
	}
}

void Player::Draw()
{
	DrawRotaGraph(drawPos.x, drawPos.y, 1, 0, gh, false);
}

void Player::CheckIsLive()
{
}

void Player::Init()
{
}

void Player::MoveUp()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {0, -1, 0};
}

void Player::MoveRight()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {1, 0, 0};
}

void Player::MoveDown()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {0, 1, 0};
}

void Player::MoveLeft()
{
	//���[�J���|�W�V�����̈ړ�
	localPos += {-1, 0, 0};
}
