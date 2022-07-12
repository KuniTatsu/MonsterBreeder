#pragma once
#include<functional>
#include"Object.h"

class Player :public Object
{
public:
	//ローカル座標を入れる
	Player(int StartX, int StartY);
	~Player();

	//毎フレーム実行の更新関数
	void Update();
	//毎フレーム実行の描画関数
	void Draw();

	//生死確認関数
	void CheckIsLive();

private:
	//初期化関数
	void Init();

	//移動関数 上下左右

	void MoveUp();

	void MoveRight();

	void MoveDown();

	void MoveLeft();

	void MoveDummy() {};


	const std::function< void(Player*) > MOVEFUNC[4] = { &Player::MoveUp,&Player::MoveRight,&Player::MoveDown,&Player::MoveLeft };


};

