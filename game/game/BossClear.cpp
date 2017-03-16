#include "stdafx.h"
#include "BossClear.h"


CBossClear::CBossClear()
{

}


CBossClear::~CBossClear()
{

}


void CBossClear::Init()
{
	position = D3DXVECTOR2(480.0f, 270.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(0, 255, 255, 255);
	texFileName = "Asset/model/clear.png";
	C2DImage::Init();
	Clear = false;
}


void CBossClear::Update()
{
	if (Clear == true)
	{
		static int i = 0;
		if (i < 255)
		{
			backColor = D3DCOLOR_ARGB(i++, 255, 255, 255);
		}
		//SE‚ð–Â‚ç‚·ƒtƒ‰ƒOB
		if (flag == false)
		{
			SEGoal.reset(new CSoundSource);
			SEGoal->Init("Asset/Sound/goal.wav");
			SEGoal->Play(false);
			flag = true;
		}
		SetupMatrices();
	}
}


void CBossClear::Render(LPD3DXSPRITE pSprite)
{
	if (Clear == true)
	{
		C2DImage::Render(pSprite);
	}
}