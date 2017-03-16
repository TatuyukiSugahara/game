#include "stdafx.h"
#include "BossLifeChip.h"


CBossLifeChip::CBossLifeChip()
{

}


CBossLifeChip::~CBossLifeChip()
{
}

void CBossLifeChip::Init()
{
	position = D3DXVECTOR2(30.0f, 30.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/ha-to.png";
	C2DImage::Init();
}

void CBossLifeChip::Update()
{
	SetupMatrices();
}
