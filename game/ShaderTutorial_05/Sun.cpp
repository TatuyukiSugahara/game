#include "stdafx.h"
#include "Sun.h"
#include "Stage.h"

//�R���X�g���N�^
CSun::CSun()
{
	//�������B
	position = D3DXVECTOR3(30.0f, 5.0f, 100.0f);
	scale = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}
//�f�X�g���N�^
CSun::~CSun()
{
}
//�������B
void CSun::Init()
{
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.5f, 1.5f, 1.5f, 1.0f));

	modelData.LoadModelData("Asset/model/sun.x", &animation);
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);
}
//�X�V�B
void CSun::Update()
{

	skinmodel.UpdateWorldMatrix({ position.x + g_stage->GetPlayer()->GetPos().x, position.y, position.z }, rotation, scale);

}
//�`��B
void CSun::Render()
{
	skinmodel.Draw(&g_stage->GetCamera()->GetViewMatrix(), &g_stage->GetCamera()->GetProjectionMatrix(), false);
}
