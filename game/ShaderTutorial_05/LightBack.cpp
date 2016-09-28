#include "stdafx.h"
#include "LightBack.h"


CLightBack::CLightBack()
{
}


CLightBack::~CLightBack()
{
}

void CLightBack::Init()
{
	//���C�g���������B
	ZeroMemory(m_diffuseLightDirection, sizeof(m_diffuseLightDirection));
	ZeroMemory(m_diffuseLightColor, sizeof(m_diffuseLightColor));
}

void CLightBack::Update()
{
	//���C�g�̌���
	m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_diffuseLightDirection[3] = D3DXVECTOR4(-0.75f, -0.75f, 0.75f, 1.0f);
	m_diffuseLightDirection[4] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);

	//�f�B�t���[�Y���C�g�B�F
	m_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
	m_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
	m_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
	m_diffuseLightColor[3] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);

	//�����B
	m_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}