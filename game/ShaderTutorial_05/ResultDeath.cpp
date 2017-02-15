#include "stdafx.h"
#include "ResultDeath.h"


CResultDeath::CResultDeath()
{
}


CResultDeath::~CResultDeath()
{
	if (SEDeath)
	{
		delete SEDeath;
	}
}

void CResultDeath::Init()
{
	position = D3DXVECTOR2(475, 260);
	angle = 0;
	scale = D3DXVECTOR2(1.5f, 1.2f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/result.png";
	C2DImage::Init();
	SEDeath = new CSoundSource;
	SEDeath->Init("Asset/Sound/death.wav");
	SEDeath->Play(false);
}

void CResultDeath::Update()
{
	this->SetupMatrices();
}