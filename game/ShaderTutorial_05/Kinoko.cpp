#include "stdafx.h"
#include "Kinoko.h"
#include "CalcAABBSizeFromMesh.h"
#include "stage.h"
#include "Sound\SoundSource.h"

//コンストラクタ
CKinoko::CKinoko()
{
	//初期化。
	D3DXMatrixIdentity(&mWorld);
	position.x = 8.0f;
	position.y = 5.0f;
	position.z = 0.0f;

	movespeed.x = 0.0f;
	movespeed.y = 0.0f;
	movespeed.z = 0.0f;

	radius = 0.3f;
}
//デストラクタ
CKinoko::~CKinoko()
{
}
//初期化。
void CKinoko::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/kinoko.x");
	IsIntersect.CollisitionInitialize(&position, radius);//あたり判定初期化
	model.SetShadowReceiverFlag(false);

	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;

	kinoko = false;		//キノコゲットしていない。
	state = none;		//キノコ出現していない。
}
//更新。
void CKinoko::Update()
{
	/*AABB*/
	if (m_aabbMax.x > g_stage->GetPlayer()->GetAABBMin().x
		&& m_aabbMin.x < g_stage->GetPlayer()->GetAABBMax().x
		&& m_aabbMax.y > g_stage->GetPlayer()->GetAABBMin().y
		&& m_aabbMin.y < g_stage->GetPlayer()->GetAABBMax().y

		)
	{
		kinoko = true;			//プレイヤーとあたったのでゲットした。
		CSoundSource* SESuper = new CSoundSource;
		SESuper->Init("Asset/Sound/super.wav");
		SESuper->Play(false);
		state = none;			//キノコ出現しなくなる
	}
	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_positionからの移動量(あたり判定)

	movespeed.x = 1.0f;
	m_aabbMax += IsIntersect.GetAddPos();
	m_aabbMin += IsIntersect.GetAddPos();

	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CKinoko::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
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
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//開放。
void CKinoko::Release()
{
	model.Release();
}