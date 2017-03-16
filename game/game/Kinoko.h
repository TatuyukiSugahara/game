#pragma once
#include "Model.h"
#include "IsIntersect\IsIntersect.h"

class IPlayerCollisionCallback;

class CKinoko {
public:
	enum class KinokoState
	{
		none,	//�L�m�R���łĂȂ�
		Leave	//�L�m�R���o�Ă���
	};
	//�R���X�g���N�^
	CKinoko();
	//�f�X�g���N�^
	~CKinoko();
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
	void SetKinoko(const bool& flag)
	{
		kinoko = flag;
	}
	const bool& GetKinoko() const
	{
		return kinoko;
	}
	//�X�e�[�g�Z�b�g
	void SetState(const KinokoState& kinoko)
	{
		state = kinoko;
	}
	//�X�e�[�g�Q�b�g
	const KinokoState& GetState() const
	{
		return state;
	}
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	D3DXVECTOR3				movespeed;
	float					radius;
	KinokoState				state;			//�L�m�R�̏��
	bool					kinoko;			//�L�m�R���v���C���[�̓Q�b�g���Ă���H
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
};