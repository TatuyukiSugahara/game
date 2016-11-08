#include "stdafx.h"
#include "StageBack.h"
#include "Stage.h"

//�R���X�g���N�^
CStageBack::CStageBack()
{
	//�������B

	D3DXMatrixIdentity(&mWorld);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//�f�X�g���N�^
CStageBack::~CStageBack()
{
}
//�������B
void CStageBack::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/sky.x");
	model.SetShadowReceiverFlag(false);
}
//�X�V�B
void CStageBack::Update()
{	
	
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
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	targetPos = g_stage->GetPlayer()->GetPos();
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, targetPos.x, targetPos.y - position.y, targetPos.z);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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
void CStageBack::Release()
{
	model.Release();
}