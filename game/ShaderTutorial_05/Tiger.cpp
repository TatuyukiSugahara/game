#include "stdafx.h"
#include "Tiger.h"

//�R���X�g���N�^
Tiger::Tiger()
{
	//�������B
	
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mRotation);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
}
//�f�X�g���N�^
Tiger::~Tiger()
{
}
//���W��ݒ�B
void Tiger::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}
//�������B
void Tiger::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "tiger.x");
}
//�X�V�B
void Tiger::Update()
{
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
void Tiger::Render( 
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
void Tiger::Release()
{
	model.Release();
}