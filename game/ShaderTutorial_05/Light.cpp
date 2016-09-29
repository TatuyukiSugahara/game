#include "stdafx.h"
#include "Light.h"


CLight::CLight()
{
}


CLight::~CLight()
{
}

void CLight::Init()
{
	//ライトを初期化。
	ZeroMemory(m_diffuseLightDirection, sizeof(m_diffuseLightDirection));
	ZeroMemory(m_diffuseLightColor, sizeof(m_diffuseLightColor));
}

void CLight::Update()
{
	//ライトの向き
	m_diffuseLightDirection[0] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_diffuseLightDirection[3] = D3DXVECTOR4(-0.75f, -0.75f, 0.75f, 1.0f);

	//ディフューズライト。色
	m_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_diffuseLightColor[1] = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	m_diffuseLightColor[2] = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	m_diffuseLightColor[3] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);

	//環境光。
	m_ambientLight = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
}