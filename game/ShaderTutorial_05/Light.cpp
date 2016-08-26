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
	//���C�g���������B
	ZeroMemory(m_diffuseLightDirection, sizeof(m_diffuseLightDirection));
	ZeroMemory(m_diffuseLightColor, sizeof(m_diffuseLightColor));
}

void CLight::Update()
{
	//���C�g�̌���
	m_diffuseLightDirection[0] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	//g_diffuseLightDirection[1] = D3DXVECTOR4(0.707f, 0.0f, 0.0f, 1.0f);
	//g_diffuseLightDirection[2] = D3DXVECTOR4(-0.707f, 0.0f, 0.0f, 1.0f);
	//g_diffuseLightDirection[3] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);

	//�f�B�t���[�Y���C�g�B�F
	m_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//g_diffuseLightColor[1] = D3DXVECTOR4(0.707, 0.0f, 0.0f, 1.0f);
	//g_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f);
	//g_diffuseLightColor[3] = D3DXVECTOR4(0.25f, 0.0f, 0.0f, 1.0f);

	//�����B
	m_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}