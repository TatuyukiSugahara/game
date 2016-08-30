#include "stdafx.h"
#include "HatenaBox.h"
#include "Player.h"
#include "CalcAABBSizeFromMesh.h"

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
void CHatenaBox::Init(LPDIRECT3DDEVICE9 pd3dDevice,CPlayer* player)
{
	model.Init(pd3dDevice, "hatena_box.x");
	this->player = player;

	Item = false;
	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;
}
//�X�V�B
void CHatenaBox::Update()
{
	if (m_aabbMin.x < player->GetPos().x
		&& m_aabbMin.y < player->GetPos().y
		&& m_aabbMax.x > player->GetPos().x
		&& m_aabbMax.y > player->GetPos().y
		)
	{
		Item = true;
	}

	
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