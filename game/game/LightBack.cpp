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
	ZeroMemory(diffuseLightDirection, sizeof(diffuseLightDirection));
	ZeroMemory(diffuseLightColor, sizeof(diffuseLightColor));
}

void CLightBack::Update()
{
	//���C�g�̌���
	//diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	//diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//diffuseLightDirection[3] = D3DXVECTOR4(-0.75f, -0.75f, 0.75f, 1.0f);
	//diffuseLightDirection[4] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);

	////�f�B�t���[�Y���C�g�B�F
	//diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
	//diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
	//diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
	//diffuseLightColor[3] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);

	//�����B
	ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}