#include "stdafx.h"
#include "Saboten.h"
#include "Map\stage.h"
#include "Result/ResultScene.h"

//�R���X�g���N�^
CSaboten::CSaboten()
{
	//�������B

	D3DXMatrixIdentity(&world);
	position = { 39.0f, 1.25f, 0.0f };
}
//�f�X�g���N�^
CSaboten::~CSaboten()
{
}
//�������B
void CSaboten::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/sabo.x");
}
//�X�V�B
void CSaboten::Update()
{
	//BOOL hit;//�q�b�g������
	//FLOAT distance;	//����
	D3DXVECTOR3 dir = position - g_stage->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = g_stage->GetPlayer()->GetPos();
	D3DXVec3Normalize(&dir, &dir);
	D3DXMATRIX InverseMat;
	D3DXMATRIX InverseRot;
	D3DXMatrixInverse(&InverseMat, NULL, &world);
	D3DXMatrixInverse(&InverseRot, NULL, &rotation);

	D3DXVec3TransformCoord(&pos, &pos, &InverseMat);
	D3DXVec3TransformCoord(&dir, &dir, &InverseRot);
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
}
//�`��B
void CSaboten::Render(
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
		world,
		rotation,
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
void CSaboten::Release()
{
	model.Release();
}