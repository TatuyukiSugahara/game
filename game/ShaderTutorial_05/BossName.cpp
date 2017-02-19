#include "stdafx.h"
#include "BossName.h"


CBossName::CBossName()
{

}


CBossName::~CBossName()
{
}

void CBossName::Init()
{
	position = D3DXVECTOR2(300.0f, 480.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/bossname.png";
	C2DImage::Init();
}

void CBossName::Update()
{
	SetupMatrices();
}
