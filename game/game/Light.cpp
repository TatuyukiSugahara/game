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
	ZeroMemory(diffuseLightDirection, sizeof(diffuseLightDirection));
	ZeroMemory(diffuseLightColor, sizeof(diffuseLightColor));
}

void CLight::Update()
{
	//ライトの向き
	diffuseLightDirection[0] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	diffuseLightDirection[3] = D3DXVECTOR4(-0.75f, -0.75f, 0.75f, 1.0f);

	//ディフューズライト。色
	diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	diffuseLightColor[1] = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	diffuseLightColor[2] = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	diffuseLightColor[3] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);

	//環境光。
	ambientLight = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
}