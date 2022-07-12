#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object :public std::enable_shared_from_this<Object>
{
protected:
	//描画座標
	tnl::Vector3 drawPos;

	//ローカル座標
	tnl::Vector3 localPos;


	//画像ハンドル
	int gh = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//方向
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
public:
	Object();
	//-------オブジェクトを生成した直後にこれを必ず呼ぶこと---------------//
	//オブジェクトリストへの登録
	void SetList();
	//------------------------------------------------------------------//

	//生死状態の獲得
	inline bool& GetIsLive() {
		return isLive;
	}
	//死亡判定セット関数
	inline void	SetIsLive() {
		isLive = false;
	}

	//描画座標の取得
	inline tnl::Vector3& GetPos() {
		return drawPos;
	}
	//描画座標のセット
	inline void	SetPos(tnl::Vector3 Pos) {
		drawPos = Pos;
	}
	//ローカル座標の取得
	inline tnl::Vector3& GetLocalPos() {
		return localPos;
	}
	//ローカル座標のセット
	inline void	SetLocalPos(tnl::Vector3 Pos) {
		localPos = Pos;
	}


	virtual~Object() {};

	//*******純粋仮想関数 継承先で実装************//
	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Init() = 0;
	//生死確認関数
	virtual	void CheckIsLive() = 0;

private:
};

