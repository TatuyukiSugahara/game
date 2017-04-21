#include "stdafx.h"
#include "Block.h"

//�R���X�g���N�^
CBlock::CBlock()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 0.0f;
	position.y =- 0.5f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CBlock::~CBlock()
{
}
//�������B
void CBlock::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/stage1.x");
	model.SetShadowReceiverFlag(true);
}
//�X�V�B
void CBlock::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CBlock::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	model.Render(
		pd3dDevice,
		mWorld,
		mRotation,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		numDiffuseLight,
		false
		);
}
//�J���B
void CBlock::Release()
{
	model.Release();
}