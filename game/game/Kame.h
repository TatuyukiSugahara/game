#pragma once
#include "character\CharacterController.h"

class CKame {
public:
	//�R���X�g���N�^
	CKame();
	//�f�X�g���N�^
	~CKame();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool shadow
		);
	//AABB�͈̔͂ɓ����Ă��邩�B
	void AabbUpdate();
	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//�L�����N�^�[�R���g���[���[������
	void CharConInit();
	//�L�����N�^�[�R���g���[���[�X�V
	void CharConUpdate();
	//�����蔻��B
	void Hit();
	//�������Q�b�g
	const float& GetHeight() const
	{
		return HEIGHT;
	}
	//���a���Q�b�g
	const float& GetRadius() const
	{
		return RADIUS;
	}
private:
	D3DXVECTOR3				position;		//���W
	D3DXVECTOR3				scale;			//�傫��
	D3DXQUATERNION			rotation;		//��]
	D3DXVECTOR3				moveSpeed;		//�ړ����x
	SkinModel				skinModel;
	SkinModelData			modelData;
	Animation				animation;
	CLight					light;
	CCharacterController	characterController;	//�L�����N�^�[�R���g���[���[
	const float				SPEED = 10.0f;			//���x��ݒ�B
	const float				HEIGHT = 0.5f;			//����
	const float				RADIUS = 0.5f;			//���a
};