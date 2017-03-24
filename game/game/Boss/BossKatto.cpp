#include "stdafx.h"
#include "BossKatto.h"


CBossKatto::CBossKatto()
{

}


CBossKatto::~CBossKatto()
{
}

void CBossKatto::Init()
{
	position = D3DXVECTOR2(480.0f, 270.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/bossKatto.png";
	C2DImage::Init();
	kattoFlag = false;

	
}

void CBossKatto::Update()
{
	if (kattoFlag == true)
	{
		if (!flag)
		{
			seKatto.reset(new CSoundSource);
			seKatto->Init("Asset/Sound/keihou.wav");
			seKatto->Play(false);
			flag = true;
		}
		SetupMatrices();
	}
}

void CBossKatto::Render(LPD3DXSPRITE pSprite)
{
	if (kattoFlag == true)
	{
		C2DImage::Render(pSprite);
	}
}

