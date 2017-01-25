#include "stdafx.h"
#include "TitleStart.h"


CTitleStart::CTitleStart()
{
}


CTitleStart::~CTitleStart()
{
}

void CTitleStart::Init()
{
	position = D3DXVECTOR2(465.0f, 380.0f);
	angle = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	texFileName = "Asset/model/title_start.png";
	C2DImage::Init();
}

void CTitleStart::Update()
{
	if (scale.x >= MAX_SCALE)
	{
		sca = false;
	}
	else if (scale.x <= MIN_SCALE)
	{
		sca = true;
	}
	if (sca == true)
	{
		scale += D3DXVECTOR2(0.005f, 0.005f);
	}
	else
	{
		scale -= D3DXVECTOR2(0.005f, 0.005f);
	}
	this->SetupMatrices();
}