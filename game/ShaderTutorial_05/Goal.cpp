#include "stdafx.h"
#include "Goal.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"
#include "ResultScene.h"
#include "Sound\SoundSource.h"

//コンストラクタ
CGoal::CGoal()
{
	//初期化。
	D3DXMatrixIdentity(&mWorld);
	position.x = 390.0f;
	position.y = 30.0f;
	position.z = -22.5f;
	m_aabbMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//デストラクタ
CGoal::~CGoal()
{
}
//初期化。
void CGoal::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/goal.x");
	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;
}
//更新。
void CGoal::Update()
{
	/*AABB*/
	if (m_aabbMax.x > g_stage->GetPlayer()->GetAABBMin().x
		&& m_aabbMin.x < g_stage->GetPlayer()->GetAABBMax().x
		&& m_aabbMax.y > g_stage->GetPlayer()->GetAABBMin().y
		&& m_aabbMin.y < g_stage->GetPlayer()->GetAABBMax().y
		&& m_aabbMax.z > g_stage->GetPlayer()->GetAABBMin().z
		&& m_aabbMin.z < g_stage->GetPlayer()->GetAABBMax().z

		)
	{
		CSoundSource* SEGoal = new CSoundSource;
		SEGoal->Init("Asset/Sound/goal.wav");
		SEGoal->Play(false);
		g_scenemanager->SetResult(0);//ゴールした場合
		g_scenemanager->ChangeScene(GameScene::Result);
	}

	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CGoal::Render(
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
//開放。
void CGoal::Release()
{
	model.Release();
}