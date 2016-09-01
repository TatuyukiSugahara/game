#include "stdafx.h"
#include "NBlock.h"

//�R���X�g���N�^
CNBlock::CNBlock()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 6.0f;
	position.y = 4.0f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CNBlock::~CNBlock()
{
}
//�������B
void CNBlock::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "block.x");
}
//�X�V�B
void CNBlock::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CNBlock::Render(
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
		numDiffuseLight
		);
}
//�J���B
void CNBlock::Release()
{
	model.Release();
}