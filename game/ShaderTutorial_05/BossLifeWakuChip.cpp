#include "stdafx.h"
#include "BossLifeWakuChip.h"


CBossLifeWakuChip::CBossLifeWakuChip()
{

}


CBossLifeWakuChip::~CBossLifeWakuChip()
{
}

void CBossLifeWakuChip::Init()
{
	position = D3DXVECTOR2(30.0f, 30.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/ha-towaku.png";
	C2DImage::Init();
}

void CBossLifeWakuChip::Update()
{
	SetupMatrices();
}
