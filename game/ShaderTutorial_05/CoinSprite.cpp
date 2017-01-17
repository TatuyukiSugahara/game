#include "stdafx.h"
#include "CoinSprite.h"


CCoinSprite::CCoinSprite()
{
}


CCoinSprite::~CCoinSprite()
{
}

void CCoinSprite::Init()
{
	position = D3DXVECTOR2(50.0f, 32.5f);
	angle = 0;
	scale = D3DXVECTOR2(0.8f, 0.8f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/coinSprite.png";
	C2DImage::Init();
}

void CCoinSprite::Update()
{
	this->SetupMatrices();
}
