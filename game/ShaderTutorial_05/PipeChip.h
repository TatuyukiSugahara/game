#pragma once
#include "Model.h"

//�}�b�v�`�b�v�̔z�u���B
struct SPipeChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�傫��	
};
class CPipeChip
{
public:
	CPipeChip();
	~CPipeChip();
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
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
	void SetPos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void SetRot(D3DXQUATERNION rot)
	{
		rotation = rot;
	}
	void SetScale(D3DXVECTOR3 scale)
	{
		Scale = scale;
	}
private:
	Model								model;			//���f���B
	D3DXMATRIX							mRot;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;
	D3DXVECTOR3							Scale;			//�傫��
	D3DXMATRIX							mScale;			//matrix�X�P�[��
	D3DXMATRIX							mWorld;			//���[���h�s��B
	int									size;
};

