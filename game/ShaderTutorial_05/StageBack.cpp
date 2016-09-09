#include "stdafx.h"
#include "StageBack.h"

//�R���X�g���N�^
CStageBack::CStageBack()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
}
//�f�X�g���N�^
CStageBack::~CStageBack()
{
}
//�������B
void CStageBack::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/sky.x");
}
//�X�V�B
void CStageBack::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void CStageBack::Render(
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
void CStageBack::Release()
{
	model.Release();
}