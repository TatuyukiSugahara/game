#include "stdafx.h"
#include "Pipe.h"

//�R���X�g���N�^
CPipe::CPipe()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 3.0f;
	position.y = 0.25f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CPipe::~CPipe()
{
}
//�������B
void CPipe::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/pipe.x");
}
//�X�V�B
void CPipe::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CPipe::Render(
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
void CPipe::Release()
{
	model.Release();
}