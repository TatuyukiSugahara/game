#pragma once
#include "Frame\Model.h"

class CHatenaBox {
public:
	enum class HatenaState
	{
		hit,			//�v���C���[�Ɠ�������
		nohit			//�v���C���[�Ɠ������Ă��Ȃ�
	};
	//�R���X�g���N�^
	CHatenaBox();
	//�f�X�g���N�^
	~CHatenaBox();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//���W�Q�b�g
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
	//�X�e�[�g�Q�b�g
	const HatenaState& GetState() const
	{
		return state;
	}
	//�X�e�[�g�Z�b�g
	void SetState(const HatenaState& sta)
	{
		state = sta;
	}
	//���̃Q�b�g
	const btRigidBody *GetHatena() const
	{
		return rigidBodyHatena;
	}
	//�����蔻��쐬
	void CreateCollision();
	//�����蔻��ǉ�
	void AddRigidBody();		
private:
	D3DXVECTOR3				position;				//���W�B
	D3DXMATRIX				mWorld;					//���[���h�s��B
	D3DXMATRIX				mRotation;				//��]�s��B
	Model					model;					//���f���B
	HatenaState				state;					//�͂ĂȂ̏��
	btCollisionShape*		hatenaboxShape;			//�n�ʂ̃R���W�����`��B
	btRigidBody*			rigidBodyHatena = NULL;	//����
	btDefaultMotionState*	myMotionState;			//���[�V�����X�e�[�g
	bool					isAddCollision;			//�R���W�����ǉ��t���O
};