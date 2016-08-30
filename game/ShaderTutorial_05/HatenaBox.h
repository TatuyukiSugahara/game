#pragma once
#include "Model.h"

class CPlayer;

class CHatenaBox {
public:
	//�R���X�g���N�^
	CHatenaBox();
	//�f�X�g���N�^
	~CHatenaBox();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice,CPlayer* player);
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
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	bool GetItem()
	{
		return Item;
	}
	void SetItem(bool flag)
	{
		Item = flag;
	}
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;

	bool					Item;			//�A�C�e���t���O

	CPlayer*					player;
};