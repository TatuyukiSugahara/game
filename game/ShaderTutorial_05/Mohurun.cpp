#include "stdafx.h"
#include "Mohurun.h"
#include "Stage.h"
#include "BallCollision.h"


CMohurun::CMohurun()
{
	position = D3DXVECTOR3(4.0f, 1.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}


CMohurun::~CMohurun()
{
}

//初期化。
void CMohurun::Init()
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
	modelData.LoadModelData("Asset/model/enemy.X", &animation);

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	animation.PlayAnimation(0);

	state = on;

	param.texturePath = "Asset/model/star.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	parflag = false;
	parTime = 0;

	count = 0;
}
//更新。
void CMohurun::Update()
{
	if (state == on)
	{
		//ワールド行列の更新。
		animation.Update(1.0f / 60.0f);
		/*if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.75f, 0.5f) == true)
		{
			exit(0);
		}*/
		if (BallCollision(position + D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, -0.3f, 0.0f), 0.75f, 0.5f) == true)
		{
			scale = D3DXVECTOR3(1.0f, 0.2f, 1.0f);
			particleEmitter.Init(param);
			parflag = true;
			state = off;
		}
		skinmodel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), scale);
	}
	if (parflag == true)
	{
		if (MAXPAR >= parTime)
		{
			particleEmitter.Update(position);
			parTime++;
		}
		else
		{
			parflag = false;
		}
		count++;
	}
}
//描画。
void CMohurun::Render()
{
	if (count < 50)
	{
		skinmodel.Draw(&g_stage->GetCamera()->GetViewMatrix(), &g_stage->GetCamera()->GetProjectionMatrix(), false);
	}
	if (parflag == true)
	{
		particleEmitter.Render(g_stage->GetCamera()->GetViewMatrix(), g_stage->GetCamera()->GetProjectionMatrix());
	}
}
