#include "stdafx.h"
#include"ShadowMap.h"
#include "Stage.h"


void CShadowMap::Create(int w, int h)
{
	D3DXMatrixIdentity(&mRot);
	RenderTarget.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	this->h = h;
	this->w = w;


	m_near = 1.0f;
	m_far = 100.0f;
}


void CShadowMap::Draw(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix
	)
{

	g_pd3dDevice->GetViewport(&m_viewport);
	g_pd3dDevice->GetRenderTarget(0, &m_Backbuffer);
	g_pd3dDevice->GetDepthStencilSurface(&m_BackZ);

	g_pd3dDevice->SetRenderTarget(0, RenderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(RenderTarget.GetDepthStencilBuffer());

	g_pd3dDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	//D3DVIEWPORT9 viewport = { 0, 0, w, h, 0.0f, 1.0f };
	//g_pd3dDevice->SetViewport(&viewport);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	float aspect;
	//aspect = (float)viewport.Width / (float)viewport.Height;
	D3DXMatrixOrthoLH(&m_projMatrix, 20.0f, 20.0f, m_near, m_far);
	CreateLight(m_projMatrix);

	g_stage->GetPlayer()->Render
		(
		m_lvMatrix,
		m_projMatrix,
		true
		);
	g_stage->GetNBlock()->Render
		(
		m_lvMatrix,
		m_projMatrix,
		true
		);
	g_stage->GetMohu()->Render
		(
		m_lvMatrix,
		m_projMatrix,
		true
		);
	g_stage->GetBird()->Render
		(
		m_lvMatrix,
		m_projMatrix,
		true
		);
	g_stage->GetCoin()->Render
		(
		m_lvMatrix,
		m_projMatrix,
		true
		);
	g_pd3dDevice->SetRenderTarget(0, m_Backbuffer);
	g_pd3dDevice->SetDepthStencilSurface(m_BackZ);
	g_pd3dDevice->SetViewport(&m_viewport);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_shadow = RenderTarget.GetTexture();
}

void CShadowMap::CreateLight(D3DXMATRIX proj)
{
	D3DXVECTOR3 lightUp;
	float t = fabsf(D3DXVec3Dot(&m_lightDirection, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	if (fabsf((t - 1.0f)) < 0.00001f)
	{
		lightUp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	D3DXVECTOR3 target;
	D3DXVec3Add(&target, &m_lightPosition, &m_lightDirection);
	D3DXMatrixLookAtLH(&m_lvMatrix, &m_lightPosition, &target, &lightUp);
		D3DXMatrixMultiply(&m_LVPMatrix, &m_lvMatrix, &m_projMatrix);
}

void CShadowMap::Release()
{
	if (m_pEffect != nullptr) {
		//m_pEffect->Release();
		m_pEffect = nullptr;
	}
}
