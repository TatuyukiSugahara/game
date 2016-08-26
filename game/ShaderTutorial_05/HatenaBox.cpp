#include "stdafx.h"
#include "HatenaBox.h"

//�R���X�g���N�^
CHatenaBox::CHatenaBox()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 8.0f;
	position.y = 4.0f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CHatenaBox::~CHatenaBox()
{
}
//�������B
void CHatenaBox::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "hatena_box.x");
}
//�X�V�B
void CHatenaBox::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CHatenaBox::Render(
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
void CHatenaBox::Release()
{
	model.Release();
}