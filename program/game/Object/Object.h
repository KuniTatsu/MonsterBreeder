#pragma once
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;

class Object :public std::enable_shared_from_this<Object>
{
protected:
	//�`����W
	tnl::Vector3 drawPos;

	//���[�J�����W
	tnl::Vector3 localPos;


	//�摜�n���h��
	int gh = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//����
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};
public:
	Object();
	//-------�I�u�W�F�N�g�𐶐���������ɂ����K���ĂԂ���---------------//
	//�I�u�W�F�N�g���X�g�ւ̓o�^
	void SetList();
	//------------------------------------------------------------------//

	//������Ԃ̊l��
	inline bool& GetIsLive() {
		return isLive;
	}
	//���S����Z�b�g�֐�
	inline void	SetIsLive() {
		isLive = false;
	}

	//�`����W�̎擾
	inline tnl::Vector3& GetPos() {
		return drawPos;
	}
	//�`����W�̃Z�b�g
	inline void	SetPos(tnl::Vector3 Pos) {
		drawPos = Pos;
	}
	//���[�J�����W�̎擾
	inline tnl::Vector3& GetLocalPos() {
		return localPos;
	}
	//���[�J�����W�̃Z�b�g
	inline void	SetLocalPos(tnl::Vector3 Pos) {
		localPos = Pos;
	}


	virtual~Object() {};

	//*******�������z�֐� �p����Ŏ���************//
	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Init() = 0;
	//�����m�F�֐�
	virtual	void CheckIsLive() = 0;

private:
};

