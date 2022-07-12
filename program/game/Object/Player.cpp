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
	//移動感知処理
	for (int i = 0; i < static_cast<uint32_t>(GameManager::KEYDIR::MAX); ++i) {
		if (tnl::Input::IsKeyDownTrigger(gManager->nowDirKeys[i])) {
			//移動関数の配列から該当する向きの物を呼ぶ
			MOVEFUNC[i](this);

			//描画座標の更新
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
	//ローカルポジションの移動
	localPos += {0, -1, 0};
}

void Player::MoveRight()
{
	//ローカルポジションの移動
	localPos += {1, 0, 0};
}

void Player::MoveDown()
{
	//ローカルポジションの移動
	localPos += {0, 1, 0};
}

void Player::MoveLeft()
{
	//ローカルポジションの移動
	localPos += {-1, 0, 0};
}
