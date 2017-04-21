#include "stdafx.h"
#include "RotationGimmick.h"
#include "Map\Stage.h"
#include "Frame\BallCollision.h"


CRotationGimmick::CRotationGimmick()
{
	
	vector = CConst::Vec3Right;					//��]�p
	originPos = D3DXVECTOR3(15.0f, 3.0f, 0.0f);	//�I���W�i���̃|�W�V����
	position[0] = originPos + vector * 1.0f;	//1��
	position[1] = originPos + vector * 1.5f;	//2��
	position[2] = originPos + vector * 2.0f;	//3��
	scale = CConst::Vec3One;					//�傫��
	D3DXMatrixIdentity(&rotation);				//��]
}


CRotationGimmick::~CRotationGimmick()
{
}

//�������B
void CRotationGimmick::Init()
{
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//���f�������[�h�B
	for (int i = 0; i < 3; i++)
	{
		modelData[i].LoadModelData("Asset/model/coin.X", &animation);

		skinModel[i].Init(&modelData[i]);
		skinModel[i].SetLight(&light);

		skinModel[i].SetDrawToShadowMap(false);
		skinModel[i].SetShadowReceiverFlag(false);
		skinModel[i].SetNormalMap(false);
		skinModel[i].SetSpecularMap(false);
	}

	
}
//�X�V�B
void CRotationGimmick::Update()
{
	D3DXMatrixRotationZ(&rotation, D3DXToRadian(1.0f));
	D3DXVec3TransformCoord(&vector, &vector, &rotation);
	position[0] = originPos + vector * 1.0f;
	position[1] = originPos + vector * 1.5f;
	position[2] = originPos + vector * 2.0f;
	
	for (int i = 0; i < 3; i++)
	{
		skinModel[i].UpdateWorldMatrix(position[i], CConst::QuaternionIdentity, scale);
	}
	
}
//�`��B
void CRotationGimmick::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	for (int i = 0; i < 3; i++)
	{
		skinModel[i].Render(&viewMatrix, &projMatrix, false);
	}
}
