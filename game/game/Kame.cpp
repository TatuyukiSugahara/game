#include "stdafx.h"
#include "Kame.h"
#include "Stage.h"
#include "BallCollision.h"

namespace
{
	const float HANSYA = -1.0f;
}

//コンストラクタ
CKame::CKame()
{
	//初期化。
	position = D3DXVECTOR3(10.82f, 3.0f, 0.0f);
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;
	moveSpeed = CConst::Vec3Zero;
}
//デストラクタ
CKame::~CKame()
{
}
//初期化。
void CKame::Init()
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//モデルをロード。
	modelData.LoadModelData("Asset/model/koura.X", NULL);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	//キャラクターコントローラー初期化
	CharConInit();
}
//更新。
void CKame::Update()
{
	//あたり判定
	Hit();
	//キャラクターコントローラー更新
	CharConUpdate();
	//ワールド行列の更新。
	skinModel.UpdateWorldMatrix(position, rotation, scale);
}
//描画。
void CKame::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool shadow
	)
{
	skinModel.Render(&viewMatrix, &projMatrix, shadow);
}

void CKame::CharConInit()
{
	characterController.Init(RADIUS, HEIGHT, position);
	characterController.SetGravity(-50.0f);
}

void CKame::CharConUpdate()
{
	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	moveSpeed = characterController.GetMoveSpeed();
	position = characterController.GetPosition();
	characterController.SetPosition(position);
}

void CKame::Hit()
{
	if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.5f, 0.3f))
	{
		//プレイヤーと当たった時の方向を調べる
		D3DXVECTOR3 Dir = position - g_stage->GetPlayer()->GetPos();
		//Y方向はいらないため0
		Dir.y = 0.0f;
		//方向を正規化する
		D3DXVec3Normalize(&Dir, &Dir);
		//方向*スピードで移動速度を決定
		moveSpeed = Dir * SPEED;
	}
	//壁と当たった時は反射する
	if (characterController.IsKabe() == true)
	{
		moveSpeed *= HANSYA;
	}
}