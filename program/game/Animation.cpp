#include "Animation.h"
#include"Manager/GameManager.h"

Animation::Animation(std::string Gh, tnl::Vector3 Pos, int ActSpeed, int MaxIndex, int XNum, int YNum, int XSize, int YSize)
{
	//ゲームマネージャインスタンス取得
	gManager = GameManager::Instance();
	//画像の分割ロード
	gManager->LoadDivGraphEx(Gh, MaxIndex, XNum, YNum, XSize, YSize, animGh);

	pos = Pos;
	actSpeed = ActSpeed;
	maxMotionIndex = MaxIndex;
}

Animation::~Animation()
{
}

void Animation::Update()
{
	//描画する画像を選択する
	if (--actWait <= 0) {
		actIndex++;
		actWait = actSpeed;
		actIndex %= maxMotionIndex;
		//tnl::DebugTrace("\nアニメーション更新%d回目\n", actIndex);
	}
	else return;
	//画像更新
	drawGh = animGh[actIndex];
	//アニメーション終了判定
	if (drawGh == animGh[maxMotionIndex - 1])isAlive = false;

}

void Animation::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraph(pos.x, pos.y, 1, 0, drawGh, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
