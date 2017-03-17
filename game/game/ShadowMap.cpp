#include "stdafx.h"
#include"ShadowMap.h"
#include "Stage.h"


void CShadowMap::Create(int w, int h)
{
	RenderTarget.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	RenderTargetUnity.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	this->h = h;
	this->w = w;


	Near = 0.1f;
	Far = 30.0f;
}


void CShadowMap::Render(D3DXMATRIX viewMatrix)
{
	g_pd3dDevice->GetViewport(&viewport);
	//元々のレンダリングターゲットを保存。後で戻すためバックアップを行う
	g_pd3dDevice->GetRenderTarget(0, &Backbuffer);
	//元々のデプスステンシルバッファを保存。後で戻すため
	g_pd3dDevice->GetDepthStencilSurface(&BackZ);
	//レンダリングターゲットを変更する
	g_pd3dDevice->SetRenderTarget(0, RenderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(RenderTarget.GetDepthStencilBuffer());
	//書き込み先を変更したのでクリア
	g_pd3dDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//射影行列を作成
	D3DXMatrixOrthoLH(&projMatrix, 20.0f, 20.0f, Near, Far);
	//ライト作成更新
	CreateLight(projMatrix);

	//ノーマルブロックの影を描画
	g_stage->GetNBlock()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//敵もふるんの影を描画
	g_stage->GetMohu()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//敵鳥の影を描画
	g_stage->GetBird()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//コインの影を描画
	g_stage->GetCoin()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//ボスの影を描画
	g_stage->GetBoss()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//亀の影を描画
	g_stage->GetKame()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//元のレンダーターゲットに戻す
	g_pd3dDevice->SetRenderTarget(0, Backbuffer);
	g_pd3dDevice->SetDepthStencilSurface(BackZ);
	g_pd3dDevice->SetViewport(&viewport);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//テクスチャセット
	g_shadow = RenderTarget.GetTexture();
}

void CShadowMap::RenderUnity(D3DXMATRIX viewMatrix)
{
	g_pd3dDevice->GetViewport(&viewport);
	//元々のレンダリングターゲットを保存。後で戻すためバックアップを行う
	g_pd3dDevice->GetRenderTarget(0, &Backbuffer);
	//元々のデプスステンシルバッファを保存。後で戻すため
	g_pd3dDevice->GetDepthStencilSurface(&BackZ);
	//レンダリングターゲットを変更する
	g_pd3dDevice->SetRenderTarget(0, RenderTargetUnity.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(RenderTargetUnity.GetDepthStencilBuffer());
	//書き込み先を変更したのでクリア
	g_pd3dDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//射影行列を作成
	D3DXMatrixOrthoLH(&projMatrix, 20.0f, 20.0f, Near, Far);
	//ライトを作成更新
	CreateLight(projMatrix);
	//プレイヤーの影を描画
	g_stage->GetPlayer()->Render
		(
		lvMatrix,
		projMatrix,
		true
		);
	//元のレンダーターゲットに戻す
	g_pd3dDevice->SetRenderTarget(0, Backbuffer);
	g_pd3dDevice->SetDepthStencilSurface(BackZ);
	g_pd3dDevice->SetViewport(&viewport);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//プレイヤーの影テクスチャセット
	g_Unity = RenderTargetUnity.GetTexture();
}

void CShadowMap::CreateLight(D3DXMATRIX proj)
{
	//ライトビュープロジェクション行列を更新
	D3DXVECTOR3 lightUp;
	//上方向を決定
	float t = fabsf(D3DXVec3Dot(&lightDirection, &CConst::Vec3Up));
	if (fabsf((t - 1.0f)) < 0.00001f)
	{
		//ほぼ真上か真下
		lightUp = CConst::Vec3Right;
	}
	else
	{
		lightUp = CConst::Vec3Up;
	}
	D3DXVECTOR3 target;
	D3DXVec3Add(&target, &lightPosition, &lightDirection);
	D3DXMatrixLookAtLH(&lvMatrix, &lightPosition, &target, &lightUp);
	D3DXMatrixMultiply(&LVPMatrix, &lvMatrix, &projMatrix);
}

void CShadowMap::Release()
{
	if (pEffect != nullptr) {
		pEffect = nullptr;
	}
}
