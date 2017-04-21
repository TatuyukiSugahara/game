#include "stdafx.h"
#include "Kinoko.h"
#include "Frame\CalcAABBSizeFromMesh.h"
#include "Map\stage.h"
#include "Sound\SoundSource.h"

//コンストラクタ
CKinoko::CKinoko()
{
	//初期化。
	D3DXMatrixIdentity(&world);
	position = { 8.0f, 5.0f, 0.0f };
	moveSpeed = CConst::Vec3Zero;

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
	//IsIntersect.CollisitionInitialize(&position, radius);//あたり判定初期化
	model.SetShadowReceiverFlag(false);

	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), aabbMin, aabbMax);
	aabbMin += position;
	aabbMax += position;

	kinoko = false;		//キノコゲットしていない。
	state = KinokoState::none;		//キノコ出現していない。
}
//更新。
void CKinoko::Update()
{
	/*AABB*/
	if (aabbMax.x > g_stage->GetPlayer()->GetAABBMin().x
		&& aabbMin.x < g_stage->GetPlayer()->GetAABBMax().x
		&& aabbMax.y > g_stage->GetPlayer()->GetAABBMin().y
		&& aabbMin.y < g_stage->GetPlayer()->GetAABBMax().y

		)
	{
		kinoko = true;			//プレイヤーとあたったのでゲットした。
		CSoundSource* SESuper = new CSoundSource;
		SESuper->Init("Asset/Sound/super.wav");
		SESuper->Play(false);
		state = KinokoState::none;			//キノコ出現しなくなる
	}
	//IsIntersect.Intersect(&position, &movespeed, callbackList);//positionからの移動量(あたり判定)

	moveSpeed.x = 1.0f;
	//aabbMax += IsIntersect.GetAddPos();
	//aabbMin += IsIntersect.GetAddPos();

	//ワールド行列の更新。
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
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
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//開放。
void CKinoko::Release()
{
	model.Release();
}