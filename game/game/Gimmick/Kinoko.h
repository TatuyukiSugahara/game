#pragma once
#include "Frame\Model.h"
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
	//�L�m�R���Q�b�g�������̃t���O�Z�b�g
	void SetKinoko(const bool& flag)
	{
		kinoko = flag;
	}
	//�L�m�R���Q�b�g�������̃t���O�Q�b�g
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
	D3DXMATRIX				world;			//���[���h�s��B
	D3DXMATRIX				rotation;		//��]�s��B
	Model					model;			//���f���B
	D3DXVECTOR3				moveSpeed;		//�ړ����x
	float					radius;			//���a
	KinokoState				state;			//�L�m�R�̏��
	bool					kinoko;			//�L�m�R���v���C���[�̓Q�b�g���Ă���H
	D3DXVECTOR3				aabbMin;		//AABB�̍ŏ�
	D3DXVECTOR3				aabbMax;		//AABB�̍ő�
};